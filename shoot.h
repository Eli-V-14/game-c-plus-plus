//
// Created by vanget on 10/11/2025.
//

#ifndef GAME_C_SHOOT_H
#define GAME_C_SHOOT_H


class Shoot {
    public:
    Shoot(float x, float y);
    float x;
    float y;

    void drawShot();
    void update();
    void updateShot();
};


#endif //GAME_C_SHOOT_H