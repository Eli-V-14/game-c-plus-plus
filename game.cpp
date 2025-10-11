//
// Created by Eli Vang on 9/26/2025.
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
#include "settings.cpp"

using namespace std;

int main() {

    Player p = Player(SCREEN_WIDTH/2 - 15, SCREEN_HEIGHT/2 - 25, 30, 50);


    // Setting up rendering window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Paint Ball Game");
    SetTargetFPS(FPS);
    srand(time(NULL));

    while (!WindowShouldClose()) {
        // update game logic should go here
        Stats s;
        Mouse m;
        DrawBoundingBox({{1, 1, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT, 0}}, PURPLE);
        // DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);

        BeginDrawing();
        ClearBackground(WHITE);
        // everything we want to draw has to be done within Begin/End Drawing
        float delta_time = GetFrameTime();
        p.update(delta_time);
        p.drawPlayer(p.getX(), p.getY(), p.getWidth(), p.getHeight());



        m.drawDirection(p.getX(), p.getY(), p.getWidth(), p.getHeight());
        s.displayStats(p.getX(), p.getY());
        EndDrawing();
    }
    CloseWindow();
    return 0;
}