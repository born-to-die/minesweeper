#pragma once
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "colors.h"
#include "render.h"

void win(RENDER &Render) {
	
	Render.clear(' ', Black, Black);

	Render.writeLine(24, 4, "    %%  %%   %%%%   %%  %%", Green, Black);
	Render.writeLine(24, 5, "     %%%%   %%  %%  %%  %%", Green, Black);
	Render.writeLine(24, 6, "      %%    %%  %%  %%  %%", Green, Black);
	Render.writeLine(24, 7, "      %%    %%  %%  %%  %%", Green, Black);
	Render.writeLine(24, 8, "      %%     %%%%    %%%%", Green, Black);
	Render.writeLine(24, 10, "   %%   %%  %%%%%%  %%  %%", Green, Black);
	Render.writeLine(24, 11, "   %%   %%    %%    %%% %%", Green, Black);
	Render.writeLine(24, 12, "   %% % %%    %%    %% %%%", Green, Black);
	Render.writeLine(24, 13, "   %%%%%%%    %%    %%  %%", Green, Black);
	Render.writeLine(24, 14, "    %% %%   %%%%%%  %%  %%", Green, Black);

	Render.draw();
}