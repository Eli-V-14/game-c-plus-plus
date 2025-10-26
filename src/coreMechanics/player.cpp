//
// Created by vanget on 10/6/2025.
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
    idleAnimation = LoadTexture("../images/player/roninIdleFront16.png");
    runAnimation = LoadTexture("../images/player/roninRunningFront16.png");
    dashAnimation = LoadTexture("../images/player/roninDashingFront16.png");
    walkAnimation = LoadTexture("../images/player/roninWalkingFront16.png");
}

Player::~Player() {
    UnloadTexture(idleAnimation);
    UnloadTexture(runAnimation);
    UnloadTexture(dashAnimation);
    UnloadTexture(walkAnimation);
}


void Player::drawPlayer(float xOffset, float yOffset) {
    // FIXME: this will be changed so the player is drawn and not a box
    Texture2D currentAnimation;
    switch (animationState) {
        case PlayerAnimationState::WALKING:
            currentAnimation = walkAnimation;
            frameTime = 0.2f;
            speed = 300.0f;
            break;
        case PlayerAnimationState::RUNNING:
            currentAnimation = runAnimation;
            frameTime = 0.1f / 2.5f;
            speed = 1200.0f;
            break;
        // case PlayerAnimationState::DASH:
        //     currentAnimation = dashAnimation;
        //     frameTime = 0.1/FIXME;
        //     break;
        default:
            currentAnimation = idleAnimation;
            frameTime = 0.1f;
            break;
    }

    numFrames = currentAnimation.width / pixelSize;
    float frameWidth = currentAnimation.width / numFrames;
    float frameHeight = currentAnimation.height;

    // cout<<frameWidth<<" "<<frameHeight<<endl;

    Rectangle source = {frameWidth * currentFrame, 0, frameWidth, frameHeight};
    if (!facingRight) source.width =  -frameWidth;
    float scaledWidth = frameWidth * 8;
    float scaledHeight = frameHeight * 8;

    float drawX = round(x - xOffset);
    float drawY = round(y - yOffset);

    Rectangle dest = {drawX, drawY, scaledWidth, scaledHeight};
    Vector2 origin = {scaledWidth / 2, scaledHeight / 2};
    SetTextureFilter(currentAnimation, TEXTURE_FILTER_POINT);
    DrawTexturePro(currentAnimation, source, dest, origin, 0.0f, WHITE);

    DrawBoundingBox({{x - xOffset - scaledWidth/4, y - yOffset - scaledHeight/2 + crouchedHeight,0},
                {x - xOffset + scaledWidth/4, y - yOffset + scaledHeight/2, 0}}, GREEN);
    if (showMirage) {
        Color orange = {255, 165, 0, 128}; // semi-transparent
        DrawRectangle(mirageX - xOffset - w/2, mirageY - yOffset - h/2, w, h, orange);
    }
}

float dashEasing(float x) {
    return 1 - pow(1 - x, 17);
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

void Player::handleInput(float xOffset, float yOffset) {
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
        float len = sqrt(vx * vx + vy * vy);
        if (len > 0) {
            vx /= len;
            vy /= len;
        }
        // records last horizontal facing direction
        if (vx > 0) facingRight = true;
        else if (vx < 0) facingRight = false;
    }

    // dash charging
    charging = IsKeyDown(KEY_TAB);
    if (IsKeyReleased(KEY_TAB) && !isDashing) {
        float worldMouseX = GetMouseX() + xOffset;
        float worldMouseY = GetMouseY() + yOffset;

        float angle = atan2(worldMouseY - y, worldMouseX - x);
        dashDirX = cos(angle);
        dashDirY = sin(angle);

        startingDashX = x;
        startingDashY = y;

        charging = false;
        isDashing = true;
    }
}

void Player::handleDashCharge(float delta_time, PlayerCamera& pc) {
    if (charging && !isDashing) {
        dash = min(dash + delta_time * dashMultiplier, maxDashCharge);

        if (crouchProgress <= 1.0f) {
            crouchedHeight = h * 0.5f * dashEasing(crouchProgress);
            crouchProgress += delta_time;
        }

        // --- FIX: use world position of the mouse ---
        float worldMouseX = GetMouseX() + pc.camRect.x;
        float worldMouseY = GetMouseY() + pc.camRect.y;

        float dx = worldMouseX - x;
        float dy = worldMouseY - y;
        float len = sqrt(dx * dx + dy * dy);
        if (len > 0) {
            dashDirX = dx / len;
            dashDirY = dy / len;
        }

        // Mirage now points toward the mouse in world space
        mirageX = x + dashDirX * dash;
        mirageY = y + dashDirY * dash;
        showMirage = true;
    } else {
        showMirage = false;
    }
}

void Player::handleDashMovement(float delta_time) {
    if (!isDashing) return;

    crouchedHeight = 0;
    crouchProgress = 0;

    if (dashProgress < 1.0f) {
        float eased = dashEasing(dashProgress);
        x = startingDashX + dashDirX * dash * eased;
        y = startingDashY + dashDirY * dash * eased;
        dashProgress += delta_time / 0.5f;

        bool nearTarget = fabs(x - (startingDashX + dashDirX * dash)) < 5 &&
                          fabs(y - (startingDashY + dashDirY * dash)) < 5;
        if (nearTarget) resetDashing();
    } else {
        resetDashing();
    }
}

void Player::handleNormalMovement(float delta_time, float xOffset, float yOffset) {
    if (charging || isDashing) return;

    if (fabs(vx) > 0.01f || fabs(vy) > 0.01f) {
        x += vx * speed * delta_time;
        y += vy * speed * delta_time;
    }
}

void Player::updateAnimationState(PlayerCamera& pc) {
    // if (isDashing) {
    //     animationState = PlayerAnimationState::DASH;
    // }
    // else
    if ((fabs(vx) > 0.1f || fabs(vy) > 0.1f) && IsKeyDown(KEY_LEFT_SHIFT)) {
        animationState = PlayerAnimationState::RUNNING;
    }
    else if (fabs(vx) > 0.1f || fabs(vy) > 0.1f) {
        animationState = PlayerAnimationState::WALKING;
    }
    else {
        animationState = PlayerAnimationState::IDLE;
    }
}


void Player::updateMovement(float delta_time, PlayerCamera& pc) {
    float xOffset = pc.camRect.x;
    float yOffset = pc.camRect.y;

    handleInput(xOffset, yOffset);
    handleDashCharge(delta_time, pc);
    handleDashMovement(delta_time);
    handleNormalMovement(delta_time, xOffset, yOffset);
    updateAnimationState(pc);
}

void Player::updateAction(float delta_time, PlayerCamera& pc) {


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
