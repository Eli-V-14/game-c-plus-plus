//
// Created by vanget on 10/6/2025.
//

#include "mouse.h"

#include <raylib.h>

void Mouse::drawDirection(float x, float y, float w, float h, Vector2 mouse_world, Camera2D cam) {
    Vector2 origin = {x + w/2, y + h/2};
    Vector2 mouse = {mouse_world.x, mouse_world.y};

    DrawLineEx(origin, mouse, 2.5, RED);
}
