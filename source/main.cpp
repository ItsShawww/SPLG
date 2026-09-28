#include "raylib.h"
#include "cam.h"
#include "grid.h"
#include "UI.h"
#include "export.h"
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>

int main() {
    InitWindow(800, 600, "RED Logic Sim");
    SetTargetFPS(60);

    Cam cam;
    float cellSize = 60.0f;

    Grid grid(cellSize);
    UI ui;

    while (!WindowShouldClose()) {
        cam.input();

        cam.calcMouseWorldPos(cellSize);

        Rectangle exportButton = { 10.0f, (float)GetScreenHeight() - 50.0f, 100.0f, 40.0f };
        bool isExportHovered = CheckCollisionPointRec(GetMousePosition(), exportButton);
        bool isExportClicked = isExportHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (isExportClicked) {
            exportFn(grid, "run.mcfunction"); 
        }

        ui.inputUI(grid.gridCells, cam, isExportClicked);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(cam.cam);

        grid.DrawLines(cam);
        grid.DrawHovered(cam, cam.hoveredX, cam.hoveredY);

        for (const auto& cell : grid.gridCells) {
            if (cell.gate != NONE) {
                float width = (cell.x1 - cell.x) * cellSize;
                float height = (cell.y1 - cell.y) * cellSize;

                Rectangle gateRect = { 
                    (float)(cell.x * cellSize), 
                    (float)(cell.y * cellSize), 
                    width, 
                    height 
                };

                Color baseCol = (cell.gate == AND) ? BLUE : (cell.gate == OR) ? GREEN : RED;
                const char* name = (cell.gate == AND) ? "AND" : (cell.gate == OR) ? "OR" : "NOT";

                DrawRectangleRec(gateRect, Fade(baseCol, 0.4f));
                DrawRectangleLinesEx(gateRect, 2.0f, baseCol);
                DrawText(name, (int)gateRect.x + 15, (int)gateRect.y + (height / 2) - 8, 16, DARKGRAY);

                float unitSize = height / 5.0f; 

                if (cell.gate == NOT) {
                    Rectangle leftSquare = {
                        gateRect.x - 8,                    
                        gateRect.y + (2 * unitSize) + 4,   
                        12.0f,                             
                        unitSize - 8                       
                    };
                    DrawRectangleRec(leftSquare, GREEN);
                    DrawRectangleLinesEx(leftSquare, 1.0f, BLACK);

                    Rectangle rightSquare = {
                        gateRect.x + width - 4,            
                        gateRect.y + (4 * unitSize) + 4,   
                        12.0f,                             
                        unitSize - 8                       
                    };
                    DrawRectangleRec(rightSquare, RED);
                    DrawRectangleLinesEx(rightSquare, 1.0f, BLACK);
                } else {
                    int greenIndices[2] = { 1, 3 };
                    for (int j = 0; j < 2; j++) {
                        int i = greenIndices[j];
                        Rectangle leftSquare = {
                            gateRect.x - 8,                    
                            gateRect.y + (i * unitSize) + 4,   
                            12.0f,                             
                            unitSize - 8                       
                        };
                        DrawRectangleRec(leftSquare, GREEN);
                        DrawRectangleLinesEx(leftSquare, 1.0f, BLACK);
                    }

                    float rightUnitSize = height / 4.0f;
                    Rectangle rightSquare = {
                        gateRect.x + width - 4,            
                        gateRect.y + (3 * rightUnitSize) + 6,
                        12.0f,
                        rightUnitSize - 12
                    };
                    DrawRectangleRec(rightSquare, RED);
                    DrawRectangleLinesEx(rightSquare, 1.0f, BLACK);
                }
            }
        }

        EndMode2D();

        ui.drawUI();

        char hoverInfo[64];
        sprintf(hoverInfo, "Selected: [%d, %d]", cam.hoveredX, cam.hoveredY);
        DrawText(hoverInfo, 10, 10, 18, DARKBLUE);

        DrawRectangleRec(exportButton, isExportHovered ? DARKGRAY : GRAY);
        DrawText("Export", (int)exportButton.x + 22, (int)exportButton.y + 11, 16, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
