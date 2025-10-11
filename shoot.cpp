//
// Created by vanget on 10/11/2025.
//
#include <raylib.h>
#include "shoot.h"

#include <cmath>

#include "player.h"

using namespace std;

Shoot::Shoot(float x, float y) {
    this->x = x;
    this->y = y;
    angle = atan2(GetMouseY() - y, GetMouseX() - x);
    vx = cos(angle) * speed;
    vy = sin(angle) * speed;
}

void Shoot::drawShot() const {
    Vector2 v1  = {x, y};
    Vector2 v2 = {x + vx * (length / speed), y + vy * (length / speed)};
    DrawLineEx(v1, v2,  3, RED);
}

void Shoot::update(float delta_time) {
    if (!active) return;

    x += vx * delta_time;
    y += vy * delta_time;

    drawShot();

    duration += delta_time;
    if (duration >= 1.0f) {
        active = false;
    }
}

bool Shoot::isActive() const {
    return active;
}



