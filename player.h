//
// Created by vanget on 10/6/2025.
//

#ifndef PAINT_BALL_PLAYER_H
#define PAINT_BALL_PLAYER_H


class Player {
    public:
        void setX(float x);
        void setY(float y);

        void setHeight(float h);
        void setWidth(float w);

        void update(float delta_time);
        void drawPlayer();

        float getX() const;
        float getY() const;

        float getHeight() const;
        float getWidth() const;

    private:
        int x = 0;
        int y = 0;
        int h = 30;
        int w = 30;
        bool charging = false;
};


#endif //PAINT_BALL_PLAYER_H