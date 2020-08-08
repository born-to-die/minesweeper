#include <iostream>
#include "render.h"

void help(RENDER &Render) {

	Render.clear();

	//Render.clear(char(176), Black, Black);

	Render.draw();

	Render.setColor(White, Black);

	Render.gotoXY(10, 3);
	std::cout << "Your task is to open all the cells without hitting the mine";

	Render.gotoXY(30, 6);
	std::cout << char(24) << char(25) << char(26) << char(27) << " - move cursor";
	Render.gotoXY(30,8);
	std::cout << "<Enter> - open cell";
	Render.gotoXY(30, 10);
	std::cout << "<Space> - set flag";
	Render.gotoXY(30, 12);
	std::cout << "<Escape> - exit";

	_getch();

}