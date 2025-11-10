//
// Created by vanget on 10/28/2025.
//

#ifndef GAME_C_SWORD_H
#define GAME_C_SWORD_H
#include <raylib.h>

#include "weapon.h"


class Sword : public Weapon {
public:
    Sword();
    ~Sword();

    void update(float dt);
    void attack();
    void draw();
};


#endif //GAME_C_SWORD_H