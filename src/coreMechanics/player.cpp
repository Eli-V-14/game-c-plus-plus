//
// Created by vanget on 10/6/2025.
//
#include <raylib.h>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "player.h"

#include "playerCamera.h"
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

float Player::getCrouchHeight() const {
    return crouchedHeight;
}

float Player::getVelocityX() const {
    return vx;
}

float Player::getVelocityY() const {
    return vy;
}


void Player::drawPlayer(float xOffset, float yOffset) const {
    DrawRectangle(x - xOffset - w/2, y - yOffset - h/2 + crouchedHeight, w, h - crouchedHeight, ORANGE);
    DrawBoundingBox({{x - xOffset - w/2, y - yOffset - h/2 + crouchedHeight,0}, {x - xOffset + w/2, y - yOffset + h/2, 0}}, BLUE);

    if (showMirage) {
        Color orange = {255, 165, 0, 128}; // semi-transparent
        DrawRectangle(mirageX - xOffset - w/2, mirageY - yOffset - h/2, w, h, orange);
    }
}

float dashEasing(float x) {
    return 1 - pow(1 - x, 17);
}

void Player::update(float delta_time, PlayerCamera& playerCamera) {
    updateMovement(delta_time, playerCamera);
    updateAction(delta_time, playerCamera);
}

void Player::resetDashing() {
    isDashing = false;
    dashProgress = 0;
    dash = 1;
}

void Player::updateMovement(float delta_time, PlayerCamera& pc) {
    const double normalized = 1 / sqrt(2.0);
    float xOffset = pc.camRect.x;
    float yOffset = pc.camRect.y;
    vx = 0;
    vy = 0;

    bool released = IsKeyReleased(KEY_TAB);

    if (IsKeyDown(KEY_W) && !isDashing) {
        float worldMouseX = GetMouseX() + pc.camRect.x;
        float worldMouseY = GetMouseY() + pc.camRect.y;
        float angle = atan2(worldMouseY - (y), worldMouseX - (x));
        vx = cos(angle);
        vy = sin(angle);
    }

    if (vx != 0 && vy != 0) {
        vx *= normalized;
        vy *= normalized;
    }

    charging = IsKeyDown(KEY_TAB);

    if (charging && !isDashing) {
        dash += delta_time * dashMultiplier;
        if (dash > maxDashCharge) {
            dash = maxDashCharge;
        }
        if (crouchProgress <= 1.0) {
            crouchedHeight = h * 0.5 * dashEasing(crouchProgress);
            crouchProgress += delta_time;
        }
        dashDirX = vx;
        dashDirY = vy;

        mirageX = x + dashDirX * dash;
        mirageY = y + dashDirY * dash;
        showMirage = true;
    } else {
        showMirage = false;
    }

    if (released && !isDashing) {
        startingDashX = x;
        startingDashY = y;
        charging = false;
        isDashing = true;
    }

    if (!charging && !isDashing) {
        float targetX = GetMouseX();
        float targetY = GetMouseY();
        float distance = sqrt(pow(targetX - x + xOffset, 2) + pow(targetY - y + yOffset, 2));
        cout<<distance<<endl;
        if (distance >= 5) {
            x += vx * speed;
            y += vy * speed;
        }
    } else if (isDashing) {
        crouchedHeight = 0;
        crouchProgress = 0;
        if (dashProgress < 1.0f) {
            float eased = dashEasing(dashProgress);
            x = startingDashX + dashDirX * dash * eased;
            y = startingDashY + dashDirY * dash * eased;
            dashProgress += delta_time / 0.5;

            if (abs(x - (startingDashX + dashDirX * dash)) < 5 &&
                abs(y - (startingDashY + dashDirY * dash)) < 5) {
                resetDashing();
                }
        } else {
            resetDashing();
        }
    }
}

void Player::updateAction(float delta_time, PlayerCamera& pc) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !charging  && !isDashing) {
        shots.emplace_back(x, y, pc);
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
