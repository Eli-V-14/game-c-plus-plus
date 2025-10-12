//
// Created by vanget on 10/11/2025.
//
#include <raylib.h>
#include <cmath>

#include "shoot.h"
#include "player.h"

using namespace std;

Shoot::Shoot(float x, float y, PlayerCamera& pc) : x(x), y(y), pc(&pc){
    // Compute angle from player center to mouse
    float mouseWorldX = GetMouseX() + pc.camRect.x;
    float mouseWorldY = GetMouseY() + pc.camRect.y;
    angle = atan2(mouseWorldY - y, mouseWorldX - x);
    vx = cos(angle) * speed;
    vy = sin(angle) * speed;
}

void Shoot::drawShot() const {
    Vector2 start = { x - pc->camRect.x, y - pc->camRect.y };
    Vector2 end = { x - pc->camRect.x + cos(angle) * length, y - pc->camRect.y + sin(angle) * length };
    DrawLineEx(start, end, 9, RED);
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



