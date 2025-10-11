//
// Created by vanget on 10/6/2025.
//
#include <raylib.h>
#include <iostream>
#include "player.h"

using namespace std;

Player::Player(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}


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

void Player::drawPlayer(float x, float y, float w, float h) const {
    DrawRectangle(x, y, w, h, ORANGE);
    DrawBoundingBox({{x, y ,0}, {x+w, y+h, 0}}, BLUE);
}

float dashEasing(float dash) {
    return 1 - pow(1 - dash, 17);
}




void Player::update(float delta_time) {
    updateMovement(delta_time);
}

void Player::updateMovement(float delta_time) {
    constexpr float speed = 7.0f;
    constexpr float maxDashCharge = 400.0f;
    constexpr float dashMultipler = 1000.0f;
    const double normalized = 1 / sqrt(2.0);

    float dx = 0.0f;
    float dy = 0.0f;

    bool released = IsKeyReleased(KEY_TAB);

    // --- Capture input, but only for direction memory ---
    if (IsKeyDown(KEY_W)) {
        float angle = atan2(GetMouseY() - y - h/2, GetMouseX() - x - w/2);
        dx = cos(angle);
        dy = sin(angle);
    }

    if (dx != 0 && dy != 0) {
        dx *= normalized;
        dy *= normalized;
    }

    charging = IsKeyDown(KEY_TAB);

    if (charging && !isDashing) {
        dash += delta_time * dashMultipler;
        if (dash > maxDashCharge) {
            dash = maxDashCharge;
        }
        previousX = dx;
        previousY = dy;
        Color orange= {255, 165, 0, 128};
        DrawRectangle(x+dx*dash, y+dy*dash, w, h, orange);

    }

    if (released && !isDashing) {
        startingDashX = x;
        startingDashY = y;
        charging = false;
        isDashing = true;
    }

    if (!charging && !isDashing) {
        x += dx * speed;
        y += dy * speed;

    } else if (isDashing) {
        if (dashProgress < 0.1f) {
            float xDashProgress = previousX * dash * dashEasing(dashProgress);
            float yDashProgress = previousY * dash * dashEasing(dashProgress);

            x = startingDashX + xDashProgress;
            y = startingDashY + yDashProgress;
            dashProgress += delta_time;
        } else {
            isDashing = false;
            dashProgress = 0;
            dash = 1;
            previousX = 0;
            previousY = 0;
        }
    }
}

Rectangle Player::getRect() const {
    return Rectangle{x, y, w, h};
}
