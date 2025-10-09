//
// Created by vanget on 10/6/2025.
//
#include <raylib.h>
#include <math.h>

#include "player.h"

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

float Player::getHeight() const {
    return h;
}

float Player::getWidth() const {
    return w;
}

void Player::setX(float player_x) {
    x = player_x;
}

void Player::setY(float player_y) {
    y = player_y;
}

void Player::setHeight(float player_height) {
    h = player_height;
}

void Player::setWidth(float player_width) {
    w = player_width;
}

void Player::drawPlayer() const {
    DrawRectangle(x, y, w, h, ORANGE);
}

void Player::update(float delta_time) {
    const double normalized = 1 / sqrt(2);
    charging = IsKeyDown(KEY_LEFT_SHIFT);
    int dash = 1;
    float dy = 0;
    float dx = 0;

    if (charging) {

    }

    if (!charging) {
        if (IsKeyDown(KEY_W)) dy = -5;
        if (IsKeyDown(KEY_S)) dy = 5;
        if (IsKeyDown(KEY_A)) dx = -5;
        if (IsKeyDown(KEY_D)) dx = 5;
    }

    if (dx != 0 && dy != 0) {
        dy = dy * normalized;
        dx = dx * normalized;
    }

    x+=dx * dash;
    y+=dy * dash;
}
