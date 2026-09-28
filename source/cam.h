#ifndef CAM_H
#define CAM_H

#include"raylib.h"
#include <iostream>
#include <cmath>
#include <stdio.h>

class Cam{
    public:
        Camera2D cam {0};
        Vector2 mouseWorldPos;
        int hoveredX, hoveredY;

        Cam();
        void input();
        void calcMouseWorldPos(int cellSize);
};

#endif
