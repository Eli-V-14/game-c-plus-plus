//
// Created by vanget on 10/11/2025.
//

#ifndef GAME_C_SHOOT_H
#define GAME_C_SHOOT_H
#include "playerCamera.h"


class Shoot {
    public:
    Shoot(float x, float y, PlayerCamera& pc);
    float x;
    float y;
    float vx;
    float vy;
    float angle;
    PlayerCamera* pc;

    float speed = 750;
    float length = 20;
    float duration = 0;
    bool active = true;


    void drawShot() const;
    void update(float delta_time);
    bool isActive() const;
};


#endif //GAME_C_SHOOT_H