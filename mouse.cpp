//
// Created by vanget on 10/6/2025.
//

#include "mouse.h"

#include <raylib.h>

void Mouse::drawDirection(float x, float y, float w, float h) {
    Vector2 origin = {x + w/2, y + h/2};
    Vector2 mouse = GetMousePosition();

    DrawLineEx(origin, mouse, 2.5, RED);
}
