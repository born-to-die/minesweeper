#pragma once
#include <ctime>
#include "field.h"

struct MINE {
    int x, y;
    bool droped;

    MINE() {
        droped = false;
    }

    void drop(FIELD &Field){
        srand(time(0)); // потом это вынести в отдельный h
        while(!droped) {
			y = rand() % Field.getSize();
			x = rand() % Field.getSize();
            if(Field.checkCell(x, y) == 0) {
                Field.fillCell(x, y);
                droped = true;
            }
        }
    }
};
