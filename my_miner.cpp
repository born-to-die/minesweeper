#include <conio.h>		// ���� ������ getch(), �� ����� � �� ����������

#include "colors.h"		// �����
#include "render.h"		// ���������
#include "cursor.h"		// ������
#include "mine.h"		// ����
#include "lobby.h"		// ��������� �����
#include "set.h"		// ����� ��������
#include "help.h"		// ����� ������
#include "lose.h"		// ����� ���������
#include "win.h"		// ����� ��������

int main()
{	
	system("title Minesweeper");

	RENDER Render(true); // �������� ������� ���������, ���������: bool <������� �� ���������>
	
	int size = 10, mines; // ������ ���� � ���-�� ��� (�� ������������� � set.h set())

	Render.setCursor(false);

	lobby(Render); // ����� "�����������"
	set(Render, size, mines); // ����� � ����������� ������� ���� � ���-�� ���
	help(Render);  // ����� � �����������

	RESTART: // ��-�� ��� ����� ��� GOTO, ��� ��� ��-�� ��������������� � ���� ������������ ���������, �������� � �������� � ����� ������ Ũ �� �����

	MINE *Mines; // ��������� �� �������� ������ ���

	Mines = new MINE[mines]; // ������������ ������ ���

	FIELD Field(size); // �������� ���� � �������� �������� size x size

	CURSOR Cursor(Field.getX(), Field.getY(), Field.getX(), Field.getY(), size, size);

	int cursorX = Field.getX(), cursorY = Field.getY(), check = 0;

	char buffer[10], *p; // ��� ������ �����

    bool game_active = true;

    for(int i = 0; i < mines; i++) {
        Mines[i].drop(Field); // ��������� ���
    }

	Field.comfield(); // �������� ������ ������� ����� ���

	Render.clear(char(177), Black, DarkGray); // ������ ������

	Render.writeLine(Field.getX() + Field.getSize() + 10, Field.getY(), "Mines:     /    " , White, Black); // ������� � ����� ��������� 

	p = itoa(mines, buffer, 10); // ��� ������ �����: int to char

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

		Field.render(Render); // ������� ���� � ����� ���������

		// ������ ����� �� ������� ��������� ������
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

		Render.draw(); // ������������ �� (�����)

		Cursor.update(check, cursorX, cursorY); // ��������� ������ (��������� ������� �������)

		if(check == 1) { // Enter (�������� ������)
			bool mine = Field.openByPlayer(cursorX - Field.getX(), cursorY - Field.getY()); // ���� �� ���� � ���� ������ ��� ������
			if(mine == true) {
				Field.cheatAllMines();
				Field.render(Render);
				Render.draw();
				_getch();
				lose(Render); // ��������
				_getch();
				goto RESTART;
			}
			check = 0;
		}
		else if(check == 2) { // Space (����)
			Field.setFlag(cursorX - Field.getX(), cursorY - Field.getY());
			check = 0;
		}
		else if (check == 3) { // Escape
			break;
		}
		else if (check == 4) { // Home (���)
			Field.cheatAllMines();
		}

		game_active = Field.checkWin(); // ��������� ������� �� ����� (������ ��� ������, ����� ���) true - ��� ���, false - ��

		if(game_active == false)
			win(Render);

	}

	_getch();

    return 0;
}
