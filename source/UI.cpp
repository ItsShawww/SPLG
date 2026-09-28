#include"UI.h"

void UI::drawUI(){
    //GATE CONTAINER
    DrawRectangle((int)GetScreenWidth() - 200, 0, 200, GetScreenHeight(), LIGHTGRAY);
    DrawText("GATE TOOLBAR", (int)GetScreenWidth() - 180, 20, 16, DARKGRAY);

    DrawRectangleRec(btnAnd, selectedTool == AND ? DARKBLUE : BLUE);
    DrawText("AND Gate", (int)btnAnd.x + 40, (int)btnAnd.y + 12, 14, WHITE);

    DrawRectangleRec(btnOr, selectedTool == OR ? DARKGREEN : GREEN);
    DrawText("OR Gate", (int)btnOr.x + 45, (int)btnOr.y + 12, 14, WHITE);

    DrawRectangleRec(btnNot, selectedTool == NOT ? MAROON : RED);
    DrawText("NOT Gate", (int)btnNot.x + 42, (int)btnNot.y + 12, 14, WHITE);

    DrawRectangleRec(btnClear, DARKGRAY);
    DrawText("Clear All", (int)btnClear.x + 45, (int)btnClear.y + 12, 14, WHITE);
}

void UI::inputUI(std::vector<Cell>& gridCells, Cam cam, bool isInp){
    Vector2 mousePos = GetMousePosition();
    bool isMouseOverSidebar = mousePos.x > (GetScreenWidth() - 200);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mousePos, btnAnd)) selectedTool = AND;
        if (CheckCollisionPointRec(mousePos, btnOr)) selectedTool = OR;
        if (CheckCollisionPointRec(mousePos, btnNot)) selectedTool = NOT;
        if (CheckCollisionPointRec(mousePos, btnClear)) gridCells.clear();
    }
    
    if (!isMouseOverSidebar && !isInp){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && selectedTool != NONE) {
            int newX = cam.hoveredX;
            int newY = cam.hoveredY;
            int newX1 = newX + 5;
            int newY1 = newY + 5;

            bool isOverlap = false;

            for (const auto& cell : gridCells) {
                if (newX < cell.x1 && newX1 > cell.x && newY < cell.y1 && newY1 > cell.y) {
                    isOverlap = true;
                    break;
                }
            }

            if (!isOverlap) {
                Cell newCell;
                newCell.x = newX;
                newCell.y = newY;
                newCell.x1 = newX1;
                newCell.y1 = newY1;
                newCell.gate = selectedTool;
                
                gridCells.push_back(newCell);
                std::cout << "Placed gate 5x5 from [" << newX << ", " << newY << "] to [" << newX1 << ", " << newY1 << "]\n";
            } else {
                std::cout << "Placement blocked: Overlaps another gate!\n";
            }
        }
    }
}
