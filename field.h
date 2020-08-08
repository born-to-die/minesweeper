#pragma once
#include <iostream>

#include "colors.h"
#include "render.h"
#include "mine.h"

class FIELD {

private:

    int **field;				// указатель на массив с минами
	int **openField;			// указатель на массив с закрытыми ячейками
    int display_x, display_y;	// координаты отрисовки
	int size;					// размер поля
	int flags;					// кол-во флагов

public:

    FIELD(int size) {
		this->size = size;

		field = new int* [size];
		for (int count = 0; count < size; count++)
			field[count] = new int [size];

		openField = new int* [size];
		for (int count = 0; count < size; count++)
			openField[count] = new int [size];

        display_x = 40 - size;
        display_y = 5 - (size / 10);
		flags = 0;
        clear();
    }

    void clear() {
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
                field[i][j] = 0;
				openField[i][j] = 0;
            }
        }
    }

    bool checkCell(int x, int y) {
        return field[y][x] == 9 ? 1 : 0;
    }

	int getSize() {
		return size;
	}

	void openCell(int x, int y) {
		if(openField[y][x] == 2)
			flags--;
		openField[y][x] = 1;
	}

	int getOpenCell(int x, int y) {
		return openField[y][x];
	}

    void fillCell(int x, int y) {
        field[y][x] = 9;
    }

	bool openByPlayer(int x, int y) {
		openEmpty(x, y);
		if(field[y][x] == 9)
			return true;
		else
			return false;
	}

	void cheatAllMines() {
		for(int y = 0; y < size; y++) {
			for(int x = 0; x < size; x++) {
				if(field[y][x] == 9) {
					if(openField[y][x] == 2)
						flags--;
					openField[y][x] = 3;
				}
			}
		}
	}

	void comfield() {
		int i;
		for(int y = 0; y < size; y++) {
			for(int x = 0; x < size; x++) {
				i = 0;
				if(field[y][x] == 0) {
					if(y > 0) { // up check
						if(field[y - 1][x] == 9 && y - 1 >= 0)
						i++;
					}
					if(y > 0 && x < size - 1) { // up-right check
						if(field[y - 1][x + 1] == 9 && y - 1 >= 0 && x + 1 < size)
							i++;
					}
					if(x < size - 1) { // right check
						if(field[y][x + 1] == 9 && x + 1 < size)
							i++;
					}
					if(y < size - 1 && x < size - 1) { // down-right check
						if(field[y + 1][x + 1] == 9 && y + 1 < size && x + 1 < size)
							i++;
					}
					if(y < size - 1) {
						if(field[y + 1][x] == 9 && y + 1 < size)
							i++;
					}
					if(y < size - 1 && x > 0) {
						if(field[y + 1][x - 1] == 9 && y + 1 < size && x - 1 >= 0)
						i++;
					}
					if(x > 0) {
						if(field[y][x - 1] == 9 && x - 1 >= 0)
							i++;
					}
					if(x > 0 && y > 0) {
						if(field[y - 1][x - 1] == 9 && y - 1 >= 0 && x - 1 >= 0)
							i++;
					}
					field[y][x] = i;

				}
			}
		}
	}

	void setFlag(int x, int y) {
		if(openField[y][x] == 0) {
			openField[y][x] = 2;
			flags++;
		}
		else if(openField[y][x] == 2) {
			openField[y][x] = 0;
			flags--;
		}
	}

	int getX() {
		return display_x;
	}

	int getFlags() {
		return flags;
	}

	int getY() {
		return display_y;
	}

    void render(RENDER &Render) {
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
				if(openField[i][j] == 1) {
					switch(field[i][j]) {
						case 9: {
							Render.addSymbol(j + display_x, i + display_y, '*', Red, Yellow);
							break;
						}
						case 8: {
							Render.addSymbol(j + display_x, i + display_y, '8', DarkGray, Yellow);
							break;
						}
						case 7: {
							Render.addSymbol(j + display_x, i + display_y, '7', Black, LightGray);
							break;
						}
						case 6: {
							Render.addSymbol(j + display_x, i + display_y, '6', Cyan, LightGray);
							break;
						}
						case 5: {
							Render.addSymbol(j + display_x, i + display_y, '5', Red, LightGray);
							break;
						}
						case 4: {
							Render.addSymbol(j + display_x, i + display_y, '4', Blue, LightGray);
							break;
						}
						case 3: {
							Render.addSymbol(j + display_x, i + display_y, '3', LightRed, LightGray);
							break;
						}
						case 2: {
							Render.addSymbol(j + display_x, i + display_y, '2', Green, LightGray);
							break;
						}
						case 1: {
							Render.addSymbol(j + display_x, i + display_y, '1', LightBlue, LightGray);
							break;
						}
						case 0: {
							Render.addSymbol(j + display_x, i + display_y, '1', LightGray, LightGray);
							break;
						}
					}
						
				}
				else if (openField[i][j] == 2) {
					Render.addSymbol(j + display_x, i + display_y, char(16), Red, LightGray);
				}
				else if (openField[i][j] == 3) {
					Render.addSymbol(j + display_x, i + display_y, char(15), LightRed, LightGray);
				}
				else {
					Render.addSymbol(j + display_x, i + display_y, char(254), White, LightGray);
				}
            }
        }
    }

	bool checkWin() {
		for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
				if(openField[i][j] == 0 || openField[i][j] == 2) {
					if(field[i][j] != 9)
						return true;
				}
			}
		}
		return false;
	}

	int getCell(int x, int y) {
		return field[y][x];
	}

	void openEmpty(int orig_x, int orig_y) {
		
		openCell(orig_x, orig_y);
		if(field[orig_y][orig_x] == 0) {
			int count_deploy;
			bool deploy = true;

			field[orig_y][orig_x] = 10;

			while(deploy) {
				count_deploy = 0;
					for(int y = 0; y < size; y++) {
						for(int x = 0; x < size; x++) {
							if(field[y][x] == 10) {
								count_deploy++;
								field[y][x] = 11;
								if(y > 0) {
									if(field[y - 1][x] == 0 && y - 1 >= 0)
										field[y - 1][x] = 10;
								}
								if(y > 0 && x < size - 1) {
									if(field[y - 1][x + 1] == 0 && y - 1 >= 0 && x + 1 < 10)
										field[y - 1][x + 1] = 10;
								}
								if(x < size - 1) {
									if(field[y][x + 1] == 0 && x + 1 < 10)
										field[y][x + 1] = 10;
								}
								if(y < size - 1 && x < size - 1) {
									if(field[y + 1][x + 1] == 0 && y + 1 < 10 && x + 1 < 10)
										field[y + 1][x + 1] = 10;
								}
								if(y < size - 1) {
									if(field[y + 1][x] == 0 && y + 1 < 10)
										field[y + 1][x] = 10;
								}
								if(y < size - 1 && x > 0) {
									if(field[y + 1][x - 1] == 0 && y + 1 < 10 && x - 1 >= 0)
										field[y + 1][x - 1] = 10;
								}
								if(x > 0) {
									if(field[y][x - 1] == 0 && x - 1 >= 0)
										field[y][x - 1] = 10;
								}
								if(x > 0 && y > 0) {
									if(field[y - 1][x - 1] == 0 && y - 1 >= 0 && x - 1 >= 0)
										field[y - 1][x - 1] = 10;
								}



								if(y > 0) {
									if(field[y - 1][x] < 9 && y - 1 >= 0)
										openCell(x, y - 1);
								}
								if(y > 0 && x < size - 1) {
									if(field[y - 1][x + 1] < 9 && y - 1 >= 0 && x + 1 < 10) 
										openCell(x + 1, y - 1);
								}
								if(x < size - 1) {
									if(field[y][x + 1] < 9 && x + 1 < 10)
										openCell(x + 1, y);
								}
								if(y < size - 1 && x < size - 1) {
									if(field[y + 1][x + 1] < 9 && y + 1 < 10 && x + 1 < 10)
										openCell(x + 1, y + 1);
								}
								if(y < size - 1) {
									if(field[y + 1][x] < 9 && y + 1 < 10)
										openCell(x, y + 1);
								}
								if(y < size - 1 && x > 0) {
									if(field[y + 1][x - 1] < 9 && y + 1 < 10 && x - 1 >= 0)
										openCell(x - 1, y + 1);
								}
								if(x > 0) {
									if(field[y][x - 1] < 9 && x - 1 >= 0)
										openCell(x - 1, y);
								}
								if(x > 0 && y > 0) {
									if(field[y - 1][x - 1] < 9 && y - 1 >= 0 && x - 1 >= 0)
										openCell(x - 1, y - 1);
								}
							}
						}
					}
            if(count_deploy == 0)
                deploy = false;
			}
			for(int y = 0; y < size; y++) {
				for(int x = 0; x < size; x++) {
                    if(field[y][x] == 11) {
                        field[y][x] = 0;
						if(openField[y][x] == 2)
							flags--;
                        openField[y][x] = 1;
                    }
                }
            }
		}
	}

};
