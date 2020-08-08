#pragma once
#include "colors.h"
#include "render.h"

void lose(RENDER &Render) {
	
	Render.clear(' ', Black, Black);

	Render.writeLine(24, 4, "    %%  %%   %%%%   %%  %%      ", Red, Black);
	Render.writeLine(24, 5, "     %%%%   %%  %%  %%  %%      ", Red, Black);
	Render.writeLine(24, 6, "      %%    %%  %%  %%  %%      ", Red, Black);
	Render.writeLine(24, 7, "      %%    %%  %%  %%  %%      ", Red, Black);
	Render.writeLine(24, 8, "      %%     %%%%    %%%%       ", Red, Black);
	Render.writeLine(24, 10, " %%       %%%%    %%%%   %%%%%% ", Red, Black);
	Render.writeLine(24, 11, " %%      %%  %%  %%      %%     ", Red, Black);
	Render.writeLine(24, 12, " %%      %%  %%   %%%%   %%%%   ", Red, Black);
	Render.writeLine(24, 13, " %%      %%  %%      %%  %%     ", Red, Black);
	Render.writeLine(24, 14, " %%%%%%   %%%%    %%%%   %%%%%% ", Red, Black);

	Render.draw();
}