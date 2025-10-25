//
// Created by vanget on 10/6/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "playerCamera.h"
#include "shoot.h"
using namespace std;

class Player {
public:
    bool charging;
    float startingDashX;
    float startingDashY;
    vector<Shoot> shots;

    bool isDashing = false;
    bool dashed = false;

    float dash = 1;
    float dashDirX = 0;
    float dashDirY = 0;
    float dashProgress = 0;

    float crouchedHeight = 0;
    float crouchProgress = 0;
    float startDashTime = 0;

    bool showMirage = false;
    float mirageX = 0;
    float mirageY = 0;

    float speed = 400.0f;
    float maxDashCharge = 400.0f;
    float dashMultiplier = 1300.0f;

    float inputDelayTimer = 0.0f;
    bool inputEnabled = false;

    float pixelSize = 64;

    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;

    float getCrouchHeight() const;

    float getVelocityX() const;
    float getVelocityY() const;

    void setHeight(float h=30);
    void setWidth(float w=30);
    float getHeight() const;
    float getWidth() const;

    void update(float delta_time, PlayerCamera& playerCamera);
    void updateMovement(float delta_time, PlayerCamera& playerCamera);
    void updateAction(float delta_time, PlayerCamera& playerCamera);
    void resetDashing();
    void drawPlayer(float xOffset, float yOffset) const;

    Rectangle getRect() const;
    Player(float x, float y, float w, float h);

private:
    float x;
    float y;
    float w;
    float h;
    float vx = 0;
    float vy = 0;

};


#endif //PLAYER_H