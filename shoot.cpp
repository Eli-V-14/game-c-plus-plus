//
// Created by vanget on 10/11/2025.
//
#include <raylib.h>
#include "shoot.h"

#include <cmath>

using namespace std;

Shoot::Shoot(float x, float y) {
    this->x = x;
    this->y = y;
}

void Shoot::drawShot() {
    float dx = cos(atan2(GetMouseY() - y, GetMouseX() - x));
    float dy = sin(atan2(GetMouseY() - y, GetMouseX() - x));

}

void Shoot::update() {

}

void Shoot::updateShot() {

}

