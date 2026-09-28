#include"raylib.h"
#include"cam.h"
#include"grid.h"
#include"gates.h"
#include<iostream>
#include<vector>

class UI{
    public:
        GateType selectedTool = NONE;

        Rectangle btnAnd   = { (float)GetScreenWidth() - 180, 50, 160, 40 };
        Rectangle btnOr    = { (float)GetScreenWidth() - 180, 100, 160, 40 };
        Rectangle btnNot   = { (float)GetScreenWidth() - 180, 150, 160, 40 };
        Rectangle btnWire  = { (float)GetScreenWidth() - 180, 200, 160, 40 };
        Rectangle btnClear = { (float)GetScreenWidth() - 180, 260, 160, 40 };

        void inputUI(std::vector<Cell>& gridCells, Cam cam, bool isInp);
        void drawUI();
};
