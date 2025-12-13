//
// Created by vanget on 10/28/2025.
//

#ifndef GAME_C_WEAPON_H
#define GAME_C_WEAPON_H

#include "player.h"

class Weapon {
public:
    Weapon(float xOffset, float yOffset) : xOff(xOffset), yOff(yOffset) {
    } ;
    virtual ~Weapon() = default;

    virtual void update(float dt, Player* p) = 0;
    virtual void attack() = 0;
    virtual void draw(Player* p) = 0;

    float xOff;
    float yOff;

    float worldX;
    float worldY;
};


#endif //GAME_C_WEAPON_H