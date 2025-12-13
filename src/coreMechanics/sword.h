//
// Created by vanget on 10/28/2025.
//

#ifndef GAME_C_SWORD_H
#define GAME_C_SWORD_H
#include <raylib.h>

#include "weapon.h"


class Sword : public Weapon {
public:
    Sword(float xOffset, float yOffset);
    ~Sword() override;

    void update(float dt, Player* p) override;
    void attack() override;
    void draw(Player* p) override;

    bool attacking = false;

private:
    Texture2D sword;
};


#endif //GAME_C_SWORD_H