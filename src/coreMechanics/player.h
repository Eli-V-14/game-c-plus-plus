//
// Created by vanget on 10/6/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "playerCamera.h"
using namespace std;

class Weapon;

enum class PlayerAnimationState {
    IDLE,
    RUNNING,
    WALKING,
    CHARGING,
    ATTACKING
};

class Player {
public:

    // Dash
    bool charging = false;
    bool isDashing = false;
    bool dashed = false;
    float dashDirX = 0, dashDirY = 0;
    float dash = 10, dashProgress = 0;
    float startingDashX = 0, startingDashY = 0;
    float startDashTime = 0;
    float speed = 50.0f;
    float maxDashCharge = 800.0f;
    float dashMultiplier = 100.0f;
    float maxDashDistance = 500.0f;

    // Crouch
    float crouchedHeight = 0, crouchProgress = 0;

    // Mirage
    bool showMirage = false;
    float mirageX = 0, mirageY = 0;

    // Timing delay
    float inputDelayTimer = 0.0f;
    bool inputEnabled = false;

    float pixelSize = 16;

    // player characteristics
    bool facingRight = true;
    bool facingFront = true;
    bool equipped = false;
    bool isHolding = true;

    // player attacking
    bool attacking = false;
    float attackTimer = 0;
    float attackDuration = 0.3f;

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

    void updateMovement(const float dt, PlayerCamera& pc);
    static void updateAction(const float dt, PlayerCamera& pc);
    void resetDashing();

    Texture2D& getCurrentAnimation();

    void drawMirage(float frameWidth, float xOffset, float yOffset, Vector2 origin, float scaledWidth,
                    float scaledHeight) const;

    void drawWeapon(float xOffset, float yOffset) const;
    void equipWeapon(Weapon* w);

    void drawPlayer(float xOffset, float yOffset);

    void resolveCollision(const Rectangle &tile);


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
    float prevX, prevY;


    Texture2D idleFront;
    Texture2D idleBack;

    Texture2D walkFront;
    Texture2D walkBack;

    Texture2D runFront;
    Texture2D runBack;

    Texture2D chargeFront;
    Texture2D chargeBack;

    Texture2D holdIdleFront;
    Texture2D holdIdleBack;

    Texture2D holdWalkFront;
    Texture2D holdWalkBack;

    Texture2D mirageTexture;

    Texture2D attackFront;
    Texture2D attackBack;

    PlayerAnimationState animationState = PlayerAnimationState::IDLE;

    Weapon* weapon = nullptr;

    int currentFrame = 0;
    int numFrames = 4;
    float frameTime = 0.1f;
    float frameTimer = 0.0f;
};


#endif //PLAYER_H