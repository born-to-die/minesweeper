#include <conio.h>		// если убрать getch(), то можно и не подключать

#include "colors.h"		// цвета
#include "render.h"		// отрисовка
#include "cursor.h"		// курсор
#include "mine.h"		// мины
#include "lobby.h"		// стартовый экран
#include "set.h"		// экран настроек
#include "help.h"		// экран помощи
#include "lose.h"		// экран проигрыша
#include "win.h"		// экран выйгрыша

int main()
{	
	system("title Minesweeper");

	RENDER Render(true); // создание объекта отрисовки, параметры: bool <активна ли отрисовка>
	
	int size = 10, mines; // размер поля и кол-во мин (всё настраивается в set.h set())

	Render.setCursor(false);

	lobby(Render); // экран "приветствия"
	set(Render, size, mines); // экран с настройками размера поля и кол-ва мин
	help(Render);  // экран с управлением

	RESTART: // ДА-ДА ЭТО МЕТКА ДЛЯ GOTO, ОНА ТУТ ИЗ-ЗА НЕПРОДУМАННОСТИ И ЛЕНИ ПЕРЕДЕЛЫВАТЬ ПРОГРАММУ, ВОЗМОЖНО В БУДУЮЩЕМ В НОВОЙ ВЕРСИИ ЕЁ НЕ БУДЕТ

	MINE *Mines; // указатель на будующий массив мин

	Mines = new MINE[mines]; // динамический массив мин

	FIELD Field(size); // создание поля с ячейками размером size x size

	CURSOR Cursor(Field.getX(), Field.getY(), Field.getX(), Field.getY(), size, size);

	int cursorX = Field.getX(), cursorY = Field.getY(), check = 0;

	char buffer[10], *p; // для вывода счета

    bool game_active = true;

    for(int i = 0; i < mines; i++) {
        Mines[i].drop(Field); // установка мин
    }

	Field.comfield(); // нумеруем клетки которые около мин

	Render.clear(char(177), Black, DarkGray); // чистка экрана

	Render.writeLine(Field.getX() + Field.getSize() + 10, Field.getY(), "Mines:     /    " , White, Black); // заносим в буфер отрисовки 

	p = itoa(mines, buffer, 10); // для вывода счета: int to char

	if(mines < 10) {
		Render.writeLine(Field.getX() + Field.getSize() + 23, Field.getY(), "00", White, Black);
		Render.writeLine(Field.getX() + Field.getSize() + 25, Field.getY(), itoa(mines, buffer, 10), White, Black);
	}
	else if (mines >= 10 && mines < 100) {
		Render.writeLine(Field.getX() + Field.getSize() + 23, Field.getY(), "0", White, Black);
		Render.writeLine(Field.getX() + Field.getSize() + 24, Field.getY(), itoa(mines, buffer, 10), White, Black);
	}
	else
		Render.writeLine(Field.getX() + Field.getSize() + 23, Field.getY(), itoa(mines, buffer, 10), White, Black);

    while(game_active) {

		if(Field.getFlags() < 10) {
			Render.writeLine(Field.getX() + Field.getSize() + 17, Field.getY(), "00", White, Black);
			Render.writeLine(Field.getX() + Field.getSize() + 19, Field.getY(), itoa(Field.getFlags(), buffer, 10), White, Black);
		}
		else if (Field.getFlags() < 100 && Field.getFlags() >= 10) {
			Render.writeLine(Field.getX() + Field.getSize() + 17, Field.getY(), "0", White, Black);
			Render.writeLine(Field.getX() + Field.getSize() + 18, Field.getY(),itoa(Field.getFlags(), buffer, 10), White, Black);
		}
		else
			Render.writeLine(Field.getX() + Field.getSize() + 17, Field.getY(), itoa(Field.getFlags(), buffer, 10), White, Black);

		Field.render(Render); // заносим поле в буфер отрисовки

		// меняем цвета на которых находится курсор
		if(Field.getOpenCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 1) {
			if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 1) {
				Cursor.draw(Render, '1', Yellow, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 2) {
				Cursor.draw(Render, '2', LightMagenta, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 3) {
				Cursor.draw(Render, '3', LightCyan, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 4) {
				Cursor.draw(Render, '4', Brown, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 5) {
				Cursor.draw(Render, '5', Cyan, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 6) {
				Cursor.draw(Render, '6', Red, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 7) {
				Cursor.draw(Render, '7', White, DarkGray);
			}
			else if(Field.getCell(Cursor.getX()  - Field.getX(), Cursor.getY() - Field.getY()) == 8) {
				Cursor.draw(Render, '8', LightGray, DarkGray);
			}
			else {
				Cursor.draw(Render, char(254), DarkGray, DarkGray);
			}
		}
		else {
			Cursor.draw(Render, char(254), DarkGray, White);
		}

		Render.draw(); // отрисовываем всё (буфер)

		Cursor.update(check, cursorX, cursorY); // обновляем курсор (считываем нажатую клавишу)

		if(check == 1) { // Enter (открытие ячейки)
			bool mine = Field.openByPlayer(cursorX - Field.getX(), cursorY - Field.getY()); // есть ли мина в этой ячейке где курсор
			if(mine == true) {
				Field.cheatAllMines();
				Field.render(Render);
				Render.draw();
				_getch();
				lose(Render); // ПРОИГРАЛ
				_getch();
				goto RESTART;
			}
			check = 0;
		}
		else if(check == 2) { // Space (флаг)
			Field.setFlag(cursorX - Field.getX(), cursorY - Field.getY());
			check = 0;
		}
		else if (check == 3) { // Escape
			break;
		}
		else if (check == 4) { // Home (чит)
			Field.cheatAllMines();
		}

		game_active = Field.checkWin(); // проверяем выйграл ли игрок (открыл все клетки, кроме мин) true - ещё нет, false - да

		if(game_active == false)
			win(Render);

	}

	_getch();

    return 0;
}
