//
// Created by vanget on 10/6/2025.
//
#include <raylib.h>
#include <iostream>
#include "player.h"
#include "shoot.h"

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

float dashEasing(float x) {
    return 1 - pow(1 - x, 17);
}

void Player::update(float delta_time) {
    updateMovement(delta_time);
    updateAction(delta_time);
}

void Player::resetDashing() {
    isDashing = false;
    dashProgress = 0;
    dash = 1;
    previousX = 0;
    previousY = 0;
}

void Player::updateMovement(float delta_time) {
    const double normalized = 1 / sqrt(2.0);

    float dx = 0.0f;
    float dy = 0.0f;

    bool released = IsKeyReleased(KEY_TAB);

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
        dash += delta_time * dashMultiplier;
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
        float vx = dx * speed;
        float vy = dy * speed;

        float targetX = GetMouseX() - w/2;
        float targetY = GetMouseY() - h/2;

        float distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));

        if (distance >= 5) {
            x += vx;
            y += vy;
        }
    } else if (isDashing) {
        if (dashProgress < 1.0f) {
            float xDashProgress = previousX * dash * dashEasing(dashProgress);
            float yDashProgress = previousY * dash * dashEasing(dashProgress);

            if (abs(x - (startingDashX + xDashProgress)) < 5 && abs(y - (startingDashY + yDashProgress)) < 5) {
                resetDashing();
            }

            x = startingDashX + xDashProgress;
            y = startingDashY + yDashProgress;
            dashProgress += delta_time / 0.5;
        } else {
            resetDashing();
        }
    }
}

void Player::updateAction(float delta_time) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !charging  && !isDashing) {
        shots.emplace_back(x + w/2, y + h/2);
    }

    for (auto it = shots.begin(); it != shots.end(); ) {
        it->update(delta_time);
        if (!it->isActive()) {
            it = shots.erase(it);
        } else {
            ++it;
        }
    }

}

Rectangle Player::getRect() const {
    return Rectangle{x, y, w, h};
}
