#include"grid.h"

Grid::Grid(float size) {
        cellSize = size;
}

void Grid::DrawLines(Cam cam) {
    Vector2 minWorld = GetScreenToWorld2D((Vector2){ 0, 0 }, cam.cam);
    Vector2 maxWorld = GetScreenToWorld2D((Vector2){ (float)GetScreenWidth(), (float)GetScreenHeight() }, cam.cam);

    int startX = (int)floorf(minWorld.x / cellSize) - 1;
    int endX   = (int)ceilf(maxWorld.x / cellSize) + 1;
    int startY = (int)floorf(minWorld.y / cellSize) - 1;
    int endY   = (int)ceilf(maxWorld.y / cellSize) + 1;

    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            Rectangle cellRect = { (float)(x * cellSize), (float)(y * cellSize), cellSize, cellSize };
            DrawRectangleLinesEx(cellRect, 1.0f, LIGHTGRAY);
        }
    }
}

void Grid::DrawHovered(Cam cam, int &hoverX, int &hoverY) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam.cam);
    hoverX = (int)floorf(mouseWorldPos.x / cellSize);
    hoverY = (int)floorf(mouseWorldPos.y / cellSize);

    DrawRectangle((int)(hoverX * cellSize), (int)(hoverY * cellSize), (int)cellSize, (int)cellSize, Fade(BLUE, 0.3f));
    DrawRectangleLines((int)(hoverX * cellSize), (int)(hoverY * cellSize), (int)cellSize, (int)cellSize, DARKBLUE);

    char coordText[32];
    sprintf(coordText, "%d, %d", hoverX, hoverY);
    DrawText(coordText, (int)(hoverX * cellSize + 5), (int)(hoverY * cellSize + 5), 12, DARKBLUE);
}
