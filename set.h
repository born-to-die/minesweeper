#include <iostream>
#include "render.h"

void set(RENDER &Render, int &size, int &mine) {

	int cmd = 0,
		hard = 0;

	Render.clear(Black);

	Render.draw();

	Render.resetColor();

	Render.gotoXY(32, 4);
	std::cout << "More cells";

	Render.gotoXY(32, 10);
	std::cout << "Less cells";

	Render.gotoXY(24, 7);
	std::cout << "Easier";

	Render.gotoXY(43, 7);
	std::cout << "More Difficult";

	Render.gotoXY(36, 6);
	std::cout << "/\\";

	Render.gotoXY(36, 8);
	std::cout << "\\/";

	Render.gotoXY(23, 14);
	std::cout << "<Enter> - press if completed";
	Render.gotoXY(23, 15);
	std::cout << char(24) << char(25) << " - use to adjust the size";
	Render.gotoXY(23, 16);
	std::cout << char(26) << char(27) << " - uso to adjust difficulty:";
	Render.gotoXY(23, 17);
	Render.setColor(Green, Black);
	std::cout << "green = 10%";
	Render.setColor(Yellow, Black);
	std::cout << " yellow = 25%";
	Render.setColor(LightRed, Black);
	std::cout << " red = 50%";
	Render.gotoXY(23, 18);
	Render.setColor(White, Black);
	std::cout << "mines from the number of cells";

	while(cmd != 13) {

		Render.gotoXY(36, 7);

		switch(hard) {
		case 0: {
				Render.setColor(LightGreen, Black);
				break;
				}
		case 1: {
				Render.setColor(Yellow, Black);
				break;
				}
		case 2: {
				Render.setColor(LightRed, Black);
				break;
				}
		}

		if(size >= 10)
			std::cout << size;
		else
			std::cout << "0" << size;

		cmd = _getch();

		if(cmd == 72 && size < 20)
			size += 5;
		if(cmd == 80 && size > 5)
			size -= 5;
		if(cmd == 77 && hard < 2)
			hard++;
		if(cmd == 75 && hard > 0)
			hard--;
	}

	if(hard == 0) hard = 10;
	if(hard == 1) hard = 25;
	if(hard == 2) hard = 50;

	mine = (size * size * hard) / 100;

}