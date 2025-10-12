//
// Created by vanget on 10/6/2025.
//

#ifndef PAINT_BALL_MOUSE_H
#define PAINT_BALL_MOUSE_H
#include <raylib.h>


class Mouse {
    public:
    static void drawDirection(float x, float y, float w, float h, Vector2 mouse_world, Camera2D camera);
};


#endif //PAINT_BALL_MOUSE_H