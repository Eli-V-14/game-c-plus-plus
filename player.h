//
// Created by vanget on 10/6/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
using namespace std;

class Player {
public:
    bool charging;
    float startingDashX;
    float startingDashY;
    float previousX;
    float previousY;

    float dash = 1;
    bool isDashing = false;
    bool dashed = false;
    float dashProgress = 0;
    float startDashTime = 0;

    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;

    void setHeight(float h=30);
    void setWidth(float w=30);
    float getHeight() const;
    float getWidth() const;

    void update(float delta_time);
    void updateMovement(float delta_time);
    void drawPlayer(float x, float y, float w, float h) const;

    Rectangle getRect() const;
    Player(float x, float y, float w, float h);

    private:

    float x;
    float y;
    float w;
    float h;
};


#endif //PLAYER_H