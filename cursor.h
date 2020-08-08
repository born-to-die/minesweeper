#pragma once
#include <conio.h>
#include "render.h"

class CURSOR {
	private:
		int x, y, min_x, max_x, min_y, max_y;

	public:

		CURSOR(int x, int y, int min_x, int min_y, int max_x, int max_y) {
			this->x = x;
			this->y = y;
			this->min_x = min_x;
			this->min_y = min_y;
			this->max_x = max_x;
			this->max_y = max_y;
		}

		int getX() {
			return x;
		}

		int getY() {
			return y;
		}

		void draw(RENDER &Render, char symbol, color syColor, color bgColor) {
			Render.addSymbol(x, y, symbol, syColor, bgColor);
		}

		void update(int &check, int &cursorX, int &cursorY) {

			int cmd;

			cmd = _getch();

			switch(cmd) {
				case 77: // right arrow
					if(x < max_x + min_x - 1)
						x += 1;
					break;
				case 75: // left arrow
					if(x > min_x)
						x -= 1;
					break;
				case 72: // up arrow
					if(y > min_y)
						y -= 1;
					break;
				case 80: // down arrow
					if(y < max_y + min_y - 1)
						y += 1;
					break;
				case 13: { // Enter
					check = 1;
					cursorX = x;
					cursorY = y;
					break;
				}
				case 27: { // Escape
					check = 3;
					break;
				}
				case 32: { // Space
					check = 2;
					cursorX = x;
					cursorY = y;
					break;
				}
				case 71: { // Home
					check = 4;
					break;
				}
			}
		}

};