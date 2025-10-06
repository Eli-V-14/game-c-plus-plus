//
// Created by vanget on 9/26/2025.
//

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#include "player.h"
#include "mouse.h"
#include "stats.h"
using namespace std;

int main() {
    constexpr int screen_width = 1200;
    constexpr int screen_height = 800;
    Mouse m;
    Player p;
    Stats s;
    // Setting player information

    p.setWidth(30);
    p.setHeight(30);
    p.setX(screen_width/2 - p.getWidth()/2);
    p.setY(screen_height/2 - p.getHeight()/2);

    InitWindow(screen_width, screen_height, "Paint Ball Game");
    SetTargetFPS(60);
    srand(time(NULL));

    while (!WindowShouldClose()) {
        // update game logic should go here

        BeginDrawing();
        ClearBackground(WHITE);
        // everything we want to draw has to be done within Begin/End Drawing
        float delta_time = GetFrameTime();
        p.update(delta_time);
        p.drawPlayer();

        m.drawDirection(p.getX(), p.getY(), p.getWidth(), p.getHeight());
        s.displayStats(p.getX(), p.getY());
        EndDrawing();
    }
    CloseWindow();
    return 0;
}