//
// Created by Eli-V-14 on 10/6/2025.
//
#include <raylib.h>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "player.h"
#include "settings.h"
#include "playerCamera.h"
#include "shoot.h"

using namespace std;

Player::Player(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {
    idleFront = LoadTexture("../images/player/roninIdleFront16.png");
    idleBack = LoadTexture("../images/player/roninIdleBack16.png");

    runFront = LoadTexture("../images/player/roninRunFront16.png");
    runBack = LoadTexture("../images/player/roninRunBack16.png");

    walkFront = LoadTexture("../images/player/roninWalkFront16.png");
    walkBack = LoadTexture("../images/player/roninWalkBack16.png");

    chargeAnimation = LoadTexture("../images/player/roninChargeFront16.png");
    dashAnimation = LoadTexture("../images/player/roninDashFront16.png");
}

Player::~Player() {
    UnloadTexture(idleFront);
    UnloadTexture(idleBack);

    UnloadTexture(walkFront);
    UnloadTexture(walkBack);

    UnloadTexture(runFront);
    UnloadTexture(runBack);

    UnloadTexture(chargeAnimation);
    UnloadTexture(dashAnimation);
}

float dashEasing(float x) {
    return 1 - pow(1 - x, 17);
}

void Player::drawPlayer(const float xOffset, const float yOffset) {
    Texture2D currentAnimation;
    switch (animationState) {
        case PlayerAnimationState::WALKING:
            currentAnimation = facingFront ? walkFront : walkBack;
            frameTime = 0.2f;
            speed = 300.0f;
            break;
        case PlayerAnimationState::RUNNING:
            currentAnimation = facingFront ? runFront : runBack;
            frameTime = 0.1f / 2.5f;
            speed = 800.0f;
            break;
        case PlayerAnimationState::CHARGING:
            currentAnimation = chargeAnimation;
            frameTime = 0.2f;
            speed = 300.0f;
            break;
        case PlayerAnimationState::DASHING:
            currentAnimation = dashAnimation;
            frameTime = 0.1;
            speed = 300.0f;
            break;
        default:
            currentAnimation = facingFront ? idleFront : idleBack;
            frameTime = 0.1f;
            speed = 300.0f;
            break;
    }

    numFrames = currentAnimation.width / pixelSize;
    const float frameWidth = currentAnimation.width / numFrames;
    const float frameHeight = currentAnimation.height;

    if (animationState != PlayerAnimationState::CHARGING) {
        frameTime += GetFrameTime();
        if (frameTimer >= frameTime) {
            frameTimer -= frameTime;
            currentFrame = (currentFrame + 1) % numFrames;
        }
    }

    Rectangle source = {frameWidth * currentFrame, 0, frameWidth, frameHeight};
    if (!facingRight) source.width =  -frameWidth;

    const float scaledWidth = frameWidth * 8;
    const float scaledHeight = frameHeight * 8;

    const float drawX = round(x - xOffset);
    const float drawY = round(y - yOffset);

    const Rectangle dest = {drawX, drawY, scaledWidth, scaledHeight};
    const Vector2 origin = {scaledWidth / 2, scaledHeight / 2};
    SetTextureFilter(currentAnimation, TEXTURE_FILTER_POINT);
    DrawTexturePro(currentAnimation, source, dest, origin, 0.0f, WHITE);

    DrawBoundingBox({{x - xOffset - scaledWidth/4, y - yOffset - scaledHeight/2 + crouchedHeight,0},
                {x - xOffset + scaledWidth/4, y - yOffset + scaledHeight/2, 0}}, GREEN);
    if (showMirage) {
        const Texture2D mirage = LoadTexture("../images/player/roninIdleFront16.png");
        Rectangle mirageSource = {frameWidth, 0, frameWidth, frameHeight};
        if (!facingRight) mirageSource.width =  -frameWidth;
        const Rectangle mirageDest = {mirageX - xOffset - w/2, mirageY - yOffset - h/2, scaledWidth, scaledHeight};
        DrawTexturePro(mirage, mirageSource, mirageDest, origin, 0.0f, {255, 255, 255, 128});
    }
}

void Player::update(float delta_time, PlayerCamera& playerCamera) {
    frameTimer += delta_time;
    if (frameTimer >= frameTime) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
    }
    updateMovement(delta_time, playerCamera);
    updateAction(delta_time, playerCamera);
}

void Player::resetDashing() {
    isDashing = false;
    dashProgress = 0;
    dash = 1;
}

void Player::handleInput(const float xOffset, const float yOffset) {
    // Reset velocity each frame
    vx = 0;
    vy = 0;

    if (!isDashing) {
        // WASD movement
        if (IsKeyDown(KEY_W)) vy -= 1;
        if (IsKeyDown(KEY_S)) vy += 1;
        if (IsKeyDown(KEY_A)) vx -= 1;
        if (IsKeyDown(KEY_D)) vx += 1;

        // Normalize diagonal movement
        const float len = sqrt(vx * vx + vy * vy);
        if (len > 0) {
            vx /= len;
            vy /= len;
        }
        // records last horizontal facing direction
        if (vx > 0) facingRight = true;
        else if (vx < 0) facingRight = false;

        if (vy > 0) facingFront = true;
        else if (vy < 0) facingFront = false;
    }

    // dash charging
    charging = IsKeyDown(KEY_TAB);
    if (IsKeyReleased(KEY_TAB) && !isDashing) {
        const float worldMouseX = GetMouseX() + xOffset;
        const float worldMouseY = GetMouseY() + yOffset;

        const float angle = atan2(worldMouseY - y, worldMouseX - x);
        dashDirX = cos(angle);
        dashDirY = sin(angle);

        startingDashX = x;
        startingDashY = y;

        charging = false;
        isDashing = true;
    }
}

void Player::handleDashCharge(const float dt, const PlayerCamera& pc) {
    if (charging && !isDashing) {
        dash = min(dash + dt * (dashMultiplier / 0.8f), maxDashCharge);

        if (crouchProgress <= 1.0f) {
            crouchedHeight = h * 0.5f * dashEasing(crouchProgress);
            crouchProgress += dt;
        }

        const float worldMouseX = GetMouseX() + pc.camRect.x;
        const float worldMouseY = GetMouseY() + pc.camRect.y;

        const float dx = worldMouseX - x;
        const float dy = worldMouseY - y;
        const float len = sqrt(dx * dx + dy * dy);
        if (len > 0) {
            dashDirX = dx / len;
            dashDirY = dy / len;
        }

        if (dashDirX > 0) facingRight = true;
        else if (dashDirX < 0) facingRight = false;

        // Compute intended dash distance and clamp
        const float intendedDistance = dash * 5.0f; // scale for charge
        const float distance = std::min(intendedDistance, maxDashDistance);

        // Set mirage position along the clamped direction
        mirageX = x + dashDirX * distance;
        mirageY = y + dashDirY * distance;
        showMirage = true;

        float chargeFraction = dash / maxDashCharge;
        if (chargeFraction > 1.0f) chargeFraction = 1.0f;
        const float eased = dashEasing(chargeFraction);

        numFrames = chargeAnimation.width / pixelSize;
        currentFrame = min(static_cast<int>(eased * (numFrames - 1)), numFrames - 1);
    } else {
        showMirage = false;
    }
}

void Player::handleDashMovement(const float dt) {
    if (!isDashing) return;

    crouchedHeight = 0;
    crouchProgress = 0;

    if (dashProgress < 1.0f) {
        // Progress the dash (0 → 1)
        dashProgress += dt * 2.0f;
        if (dashProgress > 1.0f) dashProgress = 1.0f;

        // Apply easing
        const float eased = dashEasing(dashProgress);

        // Compute actual distance with clamp
        const float intendedDistance = dash * 5.0f;
        const float distance = std::min(intendedDistance, maxDashDistance);

        // Update player position
        const float addedX = dashDirX * distance;
        const float addedY = dashDirY * distance;
        x = startingDashX + addedX * eased;
        y = startingDashY + addedY * eased;

        const bool nearTarget = fabs(x - (startingDashX + addedX)) < 5 &&
                          fabs(y - (startingDashY + addedY)) < 5;
        if (nearTarget) resetDashing();
    } else {
        resetDashing();
    }
}

void Player::handleNormalMovement(const float dt, float xOffset, float yOffset) {
    if (charging || isDashing) return;

    if (fabs(vx) > 0.01f || fabs(vy) > 0.01f) {
        x += vx * speed * dt;
        y += vy * speed * dt;
    }
}

void Player::updateAnimationState(PlayerCamera& pc) {
    // if (isDashing) {
    //     animationState = PlayerAnimationState::DASH;
    // }
    // else
    if (IsKeyDown(KEY_TAB)) {
        animationState = PlayerAnimationState::CHARGING;
    }
    else if ((fabs(vx) > 0.1f || fabs(vy) > 0.1f) && IsKeyDown(KEY_LEFT_SHIFT)) {
        animationState = PlayerAnimationState::RUNNING;
    }
    else if (fabs(vx) > 0.1f || fabs(vy) > 0.1f) {
        animationState = PlayerAnimationState::WALKING;
    }
    else {
        animationState = PlayerAnimationState::IDLE;
    }
}


void Player::updateMovement(const float dt, PlayerCamera& pc) {
    const float xOffset = pc.camRect.x;
    const float yOffset = pc.camRect.y;

    handleInput(xOffset, yOffset);
    handleDashCharge(dt, pc);
    handleDashMovement(dt);
    handleNormalMovement(dt, xOffset, yOffset);
    updateAnimationState(pc);
}

void Player::updateAction(float dt, PlayerCamera& pc) {


    // Shots being removed from game.
    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !charging  && !isDashing) {
    //     shots.emplace_back(x, y, pc);
    // }

    // for (auto it = shots.begin(); it != shots.end(); ) {
    //     it->update(delta_time);
    //     if (!it->isActive()) {
    //         it = shots.erase(it);
    //     } else {
    //         ++it;
    //     }
    // }

}

Rectangle Player::getRect() const {
    return Rectangle{x, y, w, h};
}
