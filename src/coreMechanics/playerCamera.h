//
// Created by vanget on 10/12/2025.
//

#ifndef GAME_C_PLAYERCAMERA_H
#define GAME_C_PLAYERCAMERA_H
#include <raylib.h>


class PlayerCamera {
    public:
    float screenWidth;
    float screenHeight;

    PlayerCamera(float x, float y, float width, float height, float screenWidth, float screenHeight);
    void followPlayer(float playerX, float playerY);
    Rectangle applyCamera(const Rectangle& rect);

    Rectangle camRect;

};


#endif //GAME_C_PLAYERCAMERA_H