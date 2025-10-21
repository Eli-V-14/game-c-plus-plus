//
// Created by vanget on 10/20/2025.
//

#ifndef GAME_C_ENEMY_H
#define GAME_C_ENEMY_H
#include <raylib.h>

#include "playerCamera.h"


class Enemy {
public:
    float vx;
    float vy;

    float speed = 25.0f;
    Rectangle rect;

    bool active = true;

    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;


    void setWidth(float width);
    void setHeight(float height);
    float getWidth();
    float getHeight();

    void update(float delta_time, float playerX, float playerY, PlayerCamera& pc);
    void updateMovement(float delta_time, float playerX, float playerY, PlayerCamera& pc);
    void drawEnemy(PlayerCamera& pc) const;

    Rectangle getRect() const;
    Enemy(float x, float y, float w, float h);

private:
    float x;
    float y;
    float w;
    float h;
};


#endif //GAME_C_ENEMY_H