//
// Created by vanget on 10/12/2025.
//

#include "playerCamera.h"

#include <cmath>

PlayerCamera::PlayerCamera(float x, float y, float width, float height, float screenWidth, float screenHeight) {
    camRect = {x, y, width, height};
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

Rectangle PlayerCamera::applyCamera(const Rectangle& rect) {
    float scaleX = screenWidth / camRect.width;
    float scaleY = screenHeight / camRect.height;

    return Rectangle{(rect.x - camRect.x) * scaleX, (rect.y - camRect.y) * scaleY, rect.width * scaleX, rect.height * scaleY};
}

void PlayerCamera::followPlayer(float playerX, float playerY) {
    float deadZoneLeft   = camRect.x + camRect.width * 0.2f;
    float deadZoneRight  = camRect.x + camRect.width * 0.8f;
    float deadZoneTop    = camRect.y + camRect.height * 0.3f;
    float deadZoneBottom = camRect.y + camRect.height * 0.7f;

    if (playerX < deadZoneLeft) {
        camRect.x -= round(deadZoneLeft - playerX);
    } else if (playerX > deadZoneRight) {
        camRect.x += round(playerX - deadZoneRight);
    }

    if (playerY < deadZoneTop) {
        camRect.y -= round(deadZoneTop - playerY);
    } else if (playerY > deadZoneBottom) {
        camRect.y += round(playerY - deadZoneBottom);
    }



}

