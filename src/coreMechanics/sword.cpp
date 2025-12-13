//
// Created by vanget on 10/28/2025.
//

#include "sword.h"
#include "player.h"

Sword::Sword(float xOffset, float yOffset) : Weapon(xOffset, yOffset) {
    sword = LoadTexture("../images/player/finnSoulSword.png");
}

Sword::~Sword() {
    UnloadTexture(sword);
}


void Sword::update(float dt, Player* p) {
    draw(p);
}

void Sword::draw(Player* p) {
    float ww = sword.width;
    float wh = sword.height;
    float scale = 4.5f;

    // --- Source rectangle ---
    Rectangle swordSrc = {0, 0, ww, wh};

    // --- Base destination position ---
    float destX = - xOff;
    float destY = - yOff;

    // --- Facing-direction offsets (clean & stable) ---
    float xOff = 0.0f;

    if (p->facingFront) {
        xOff = p->facingRight ? 0.0f : -30.0f;
    } else {
        xOff = p->facingRight ? -60.0f : 40.0f;
    }

    destX += xOff;

    // Final destination rectangle
    Rectangle weaponDest = {destX, destY - 20, ww * scale, wh * scale};
    Vector2 wOrigin = { (ww * scale) / 2.0f, (wh * scale) / 2.0f };

    float angle = p->facingRight ? -30.0f : 30.0f;

    DrawTexturePro(sword, swordSrc, weaponDest, wOrigin, angle, WHITE);
}

void Sword::attack() {

}
