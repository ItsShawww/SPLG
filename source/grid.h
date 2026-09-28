#ifndef GRID_H
#define GRID_H

#include"raylib.h"
#include"cam.h"
#include"gates.h"
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<vector>

class Grid {
    private:
        float cellSize;

    public:
        std::vector<Cell> gridCells;
        Grid(float size);
        void DrawLines(Cam cam);
        void DrawHovered(Cam cam, int &hoverX, int &hoverY);
};

#endif
