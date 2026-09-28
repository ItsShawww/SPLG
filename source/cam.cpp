#include "cam.h"

Cam::Cam(){
    cam.zoom = 1.0f;
}

void Cam::input(){
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        Vector2 delta = GetMouseDelta();
        cam.target.x -= delta.x / cam.zoom;
        cam.target.y -= delta.y / cam.zoom;
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        cam.zoom += wheel * 0.1f;
        if (cam.zoom < 0.2f) cam.zoom = 0.2f;
        if (cam.zoom > 3.0f) cam.zoom = 3.0f;
    }
}

void Cam::calcMouseWorldPos(int cellSize){
    mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);
    hoveredX = (int)floorf(mouseWorldPos.x / cellSize);
    hoveredY = (int)floorf(mouseWorldPos.y / cellSize);
}
