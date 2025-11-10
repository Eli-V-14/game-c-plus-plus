//
// Created by vanget on 10/28/2025.
//

#ifndef GAME_C_WEAPON_H
#define GAME_C_WEAPON_H


class Weapon {
public:
    Weapon();
    ~Weapon();

    void update(float dt);
    void attack();
    void draw();
};


#endif //GAME_C_WEAPON_H