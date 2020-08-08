#pragma once
#include <conio.h>
#include "colors.h"
#include "render.h"

void lobby(RENDER &Render) {

	bool pressFirstFrame = true;

	Render.clear(Black);

	Render.writeLine(20, 4, "_|      _|  _|                      ", White, Black);
	Render.writeLine(20, 5, "_|_|  _|_|      _|_|_|      _|_|    ", White, Black);
	Render.writeLine(20, 6, "_|  _|  _|  _|  _|    _|  _|_|_|_|  ", White, Black);
	Render.writeLine(20, 7, "_|      _|  _|  _|    _|  _|        ", White, Black);
	Render.writeLine(20, 8, "_|      _|  _|  _|    _|    _|_|_|  ", White, Black);
	Render.writeLine(20, 10, "S   W     E     E     P    E    R", White, Black);

	Render.writeLine(0, 24, "sites.google.com/site/collapsargames/", White, DarkGray);
	Render.writeLine(0, 0, "version: 0.9", White, DarkGray);
	Render.writeLine(65, 24, "Collapsar Games", White, DarkGray);

	while(!_kbhit()) {
		Render.draw();
		if(pressFirstFrame == true) {
			Render.writeLine(25, 15, "Press any key to continue", White, Black);
			pressFirstFrame = false;
		}
		else {
			Render.writeLine(25, 15, "Press any key to continue", Black, Black);
			pressFirstFrame = true;
		}
		Sleep(500);
	}

	_getch();
}