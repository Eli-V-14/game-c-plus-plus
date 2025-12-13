//
// Created by Eli-V-14 on 10/6/2025.
//
#include <raylib.h>
#include <algorithm>
#include <iomanip>

#include "player.h"
#include "playerCamera.h"
#include "sword.h"

using namespace std;

Player::Player(const float x, const float y, const float w, const float h) : x(x), y(y), w(w), h(h) {
    idleFront = LoadTexture("../images/player/roninIdleFSheet.png");
    idleBack = LoadTexture("../images/player/roninIdleBSheet.png");

    runFront = LoadTexture("../images/player/roninRunFSheet.png");
    runBack = LoadTexture("../images/player/roninRunBSheet.png");

    walkFront = LoadTexture("../images/player/roninWalkFSheet.png");
    walkBack = LoadTexture("../images/player/roninWalkBSheet.png");

    chargeFront = LoadTexture("../images/player/roninChargeFSheet.png");
    chargeBack = LoadTexture("../images/player/roninChargeBSheet.png");

    holdIdleFront = LoadTexture("../images/player/roninIdleHoldFSheet.png");
    holdIdleBack = LoadTexture("../images/player/roninIdleHoldBSheet.png");

    holdWalkFront = LoadTexture("../images/player/roninWalkHoldFSheet.png");
    holdWalkBack = LoadTexture("../images/player/roninWalkHoldBSheet.png");

    mirageTexture = LoadTexture("../images/player/roninIdleFSheet.png");

    attackFront = LoadTexture("../images/player/roninSwingFSheet.png");
    attackBack = LoadTexture("../images/player/roninSwingBSheet.png");
}

Player::~Player() {
    UnloadTexture(idleFront);
    UnloadTexture(idleBack);

    UnloadTexture(walkFront);
    UnloadTexture(walkBack);

    UnloadTexture(runFront);
    UnloadTexture(runBack);

    UnloadTexture(chargeFront);
    UnloadTexture(chargeBack);

    UnloadTexture(holdIdleFront);
    UnloadTexture(holdIdleBack);

    UnloadTexture(mirageTexture);

    UnloadTexture(attackFront);
    UnloadTexture(attackBack);

    if (weapon) delete weapon;
}

float dashEasing(const float x) {
    return 1 - pow(1 - x, 17);
}

Texture2D& Player::getCurrentAnimation() {
    switch (animationState) {
        case PlayerAnimationState::ATTACKING:
            speed = 0; frameTime = 0.05f;
            return equipped && facingFront ? attackFront : attackBack;
        case PlayerAnimationState::WALKING:  speed = 300; frameTime = 0.2f;
            return equipped ? (facingFront ? holdWalkFront : holdWalkBack) : (facingFront ? walkFront : walkBack);
        case PlayerAnimationState::RUNNING:  speed = 800; frameTime = 0.04f;
            equipped = false;
            return facingFront ? runFront : runBack;
        case PlayerAnimationState::CHARGING: speed = 300; frameTime = 0.2f;
            equipped = false;
            return facingFront ? chargeFront : chargeBack;
        default: speed = 300; frameTime = 0.1f;
            return equipped ? (facingFront ? holdIdleFront : holdIdleBack) : (facingFront ? idleFront : idleBack);
    }
}
void Player::drawMirage(float frameWidth, float xOffset, float yOffset, Vector2 origin, float scaledWidth, float scaledHeight) const {
    Rectangle mirHeadSrc  = {frameWidth, 0,  frameWidth, 16};
    Rectangle mirHandsSrc = {frameWidth, 16, frameWidth, 16};
    Rectangle mirBodySrc  = {frameWidth, 32, frameWidth, 16};
    if (!facingRight) {
        mirHeadSrc.width = -frameWidth;
        mirHandsSrc.width = -frameWidth;
        mirBodySrc.width = -frameWidth;
    }
    const Rectangle mirageDest = {mirageX - xOffset - w/2, mirageY - yOffset - h/2, scaledWidth, scaledHeight};
    DrawTexturePro(mirageTexture, mirBodySrc, mirageDest, origin, 0.0f, {255, 255, 255, 128});
    DrawTexturePro(mirageTexture, mirHandsSrc, mirageDest, origin, 0.0f,  {255, 255, 255, 128});
    DrawTexturePro(mirageTexture, mirHeadSrc, mirageDest, origin, 0.0f,  {255, 255, 255, 128});
}

void Player::drawWeapon(float xOffset, float yOffset) const {
    if (weapon && equipped) {
        weapon->draw(const_cast<Player*>(this));
    }
}

void Player::equipWeapon(Weapon* w) {
    weapon = w;
    equipped = true;
}


void Player::drawPlayer(const float xOffset, const float yOffset) {
    const Texture2D currentAnimation = getCurrentAnimation();

    numFrames = currentAnimation.width / pixelSize;
    const float frameWidth = pixelSize;
    const float frameHeight = pixelSize;

    if (animationState != PlayerAnimationState::CHARGING) {
        frameTimer += GetFrameTime();
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

    const Vector2 origin = {scaledWidth / 2, scaledHeight / 2};
    const Rectangle dest = {drawX, drawY, scaledWidth, scaledHeight};

    Rectangle headSrc  = {frameWidth * currentFrame, 0,  frameWidth, 16};
    Rectangle handsSrc = {frameWidth * currentFrame, 16, frameWidth, 16};
    Rectangle bodySrc  = {frameWidth * currentFrame, 32, frameWidth, 16};

    if (!facingRight) {
        headSrc.width = -frameWidth;
        handsSrc.width = -frameWidth;
        bodySrc.width = -frameWidth;
    }


    if (facingFront) {
        DrawTexturePro(currentAnimation, bodySrc, dest, origin, 0.0f, WHITE);
        DrawTexturePro(currentAnimation, handsSrc, dest, origin, 0.0f, WHITE);
        if (equipped) {
            drawWeapon(xOffset, yOffset + 50);
        }
    } else {
        if (equipped) {
            drawWeapon(xOffset, yOffset + 50);
        }
        DrawTexturePro(currentAnimation, bodySrc, dest, origin, 0.0f, WHITE);
        DrawTexturePro(currentAnimation, handsSrc, dest, origin, 0.0f, WHITE);
    }
    DrawTexturePro(currentAnimation, headSrc, dest, origin, 0.0f, WHITE);



    // DrawBoundingBox({{x - xOffset - scaledWidth/4, y - yOffset - scaledHeight/2 + crouchedHeight,0},
    //             {x - xOffset + scaledWidth/4, y - yOffset + scaledHeight/2, 0}}, GREEN);

    if (showMirage) {
        drawMirage(frameWidth, xOffset, yOffset, origin, scaledWidth, scaledHeight);
    }
}

void Player::resolveCollision(const Rectangle& tile) {
    Rectangle playerRect = {x, y, w, h};

    if (!CheckCollisionRecs(playerRect, tile)) return; // no collision

    // Horizontal collision
    Rectangle horizRect = {x, prevY, w, h};
    if (CheckCollisionRecs(horizRect, tile)) {
        x = prevX; // undo horizontal movement
    }

    // Vertical collision
    Rectangle vertRect = {prevX, y, w, h};
    if (CheckCollisionRecs(vertRect, tile)) {
        y = prevY; // undo vertical movement
    }
}



void Player::update(const float dt, PlayerCamera& pc) {
    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
    }
    updateMovement(dt, pc);
    updateAction(dt, pc);
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
        vx = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
        vy = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

        if (IsKeyPressed(KEY_E)) equipped = !equipped;

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

        numFrames = chargeFront.width / pixelSize;
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
        // Calculate intended next position
        float nextX = x + vx * speed * dt;
        float nextY = y + vy * speed * dt;

        // Move player
        x = nextX;
        y = nextY;
    }
}


void Player::updateAnimationState(PlayerCamera& pc) {
    if (!attacking && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        attacking = true;
        attackTimer = 0;
        currentFrame = 0;
        animationState = PlayerAnimationState::ATTACKING;

    }
    else if (IsKeyDown(KEY_TAB)) {
        animationState = PlayerAnimationState::CHARGING;
    }
    else if ((fabs(vx) > 0.1f || fabs(vy) > 0.1f) && IsKeyDown(KEY_LEFT_SHIFT)) {
        animationState = PlayerAnimationState::RUNNING;
    }
    else if (fabs(vx) > 0.1f || fabs(vy) > 0.1f) {
        animationState = PlayerAnimationState::WALKING;
    } else {
        animationState = PlayerAnimationState::IDLE;
    }
}

void Player::updateMovement(const float dt, PlayerCamera& pc) {
    prevX = x;
    prevY = y;

    const float xOffset = pc.camRect.x;
    const float yOffset = pc.camRect.y;

    handleInput(xOffset, yOffset);
    handleDashCharge(dt, pc);
    handleDashMovement(dt);
    handleNormalMovement(dt, xOffset, yOffset);
    updateAnimationState(pc);
}

void Player::updateAction(float dt, PlayerCamera& pc) {
    // FIXME
}

Rectangle Player::getRect() const {
    return Rectangle{x, y, w, h};
}
