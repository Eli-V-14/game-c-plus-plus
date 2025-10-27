//
// Created by vanget on 10/6/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "playerCamera.h"
#include "shoot.h"
using namespace std;

enum class PlayerAnimationState {
    IDLE,
    RUNNING,
    WALKING,
    DASHING,
    CHARGING
};

class Player {
public:
    bool charging = false;
    float startingDashX = 0;
    float startingDashY = 0;
    vector<Shoot> shots;

    bool isDashing = false;
    bool dashed = false;

    float dash = 10;
    float dashDirX = 0;
    float dashDirY = 0;
    float dashProgress = 0;

    float crouchedHeight = 0;
    float crouchProgress = 0;
    float startDashTime = 0;

    bool showMirage = false;
    float mirageX = 0;
    float mirageY = 0;

    float speed = 50.0f;
    float maxDashCharge = 800.0f;
    float dashMultiplier = 100.0f;
    float maxDashDistance = 500.0f;

    float inputDelayTimer = 0.0f;
    bool inputEnabled = false;

    float pixelSize = 16;
    bool facingRight = true;

    void setX(const float x_val) {
        x = x_val;
    }
    void setY(const float y_val) {
        y = y_val;
    }
    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }

    float getCrouchHeight() const {
        return crouchedHeight;
    }

    float getVelocityX() const {
        return vx;
    }
    float getVelocityY() const {
        return vy;
    }

    void setHeight(const float height=30) {
        h = height;
    }
    void setWidth(const float width=30) {
        w = width;
    }
    float getHeight() const {
        return h;
    }
    float getWidth() const {
        return w;
    }

    void update(float dt, PlayerCamera& pc);
    void handleInput(float xOffset, float yOffset);
    void handleDashCharge(float dt, const PlayerCamera& pc);
    void handleDashMovement(float dt);
    void handleNormalMovement(float dt, float xOffset, float yOffset);
    void updateAnimationState(PlayerCamera& pc);

    void updateMovement(float dt, PlayerCamera& pc);
    void updateAction(float dt, PlayerCamera& pc);
    void resetDashing();
    void drawPlayer(float xOffset, float yOffset);


    Rectangle getRect() const;

    Player(float x, float y, float w, float h);
    ~Player();

private:
    float x;
    float y;
    float w;
    float h;
    float vx = 0;
    float vy = 0;

    Texture2D idleAnimation;
    Texture2D walkAnimation;
    Texture2D runAnimation;
    Texture2D chargeAnimation;
    Texture2D dashAnimation;

    PlayerAnimationState animationState = PlayerAnimationState::IDLE;

    int currentFrame = 0;
    int numFrames = 4;
    float frameTime = 0.1f;
    float frameTimer = 0.0f;
};


#endif //PLAYER_H