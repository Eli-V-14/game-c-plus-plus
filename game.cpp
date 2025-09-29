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
using namespace std;

void update_player(float &x, float &y) {
    const double normalized = 1 / sqrt(2);
    bool dash = false;
    float dy = 0;
    float dx = 0;

    if (IsKeyDown(KEY_W)) dy = -5;
    if (IsKeyDown(KEY_S)) dy = 5;
    if (IsKeyDown(KEY_A)) dx = -5;
    if (IsKeyDown(KEY_D)) dx = 5;
    if (IsKeyPressed(KEY_RIGHT_SHIFT)) dash = true;

    if (dx != 0 && dy != 0) {
        dy = dy * normalized;
        dx = dx * normalized;
    }

    x+=dx * (dash ? 20 : 1);
    y+=dy * (dash ? 20 : 1);
}

void draw_direction(float &x, float &y, float player_dim) {
    Vector2 origin = {x + player_dim/2, y + player_dim/2};
    Vector2 mouse = GetMousePosition();

    DrawLineEx(origin, mouse, 2.5, RED);
}

void game_info(float x, float y) {
    DrawFPS(10,70);
    DrawText(TextFormat("Player Position: X=%.2f, Y=%.2f", x, y), 10, 10, 20, BLUE);
    DrawText(TextFormat("Mouse Position: X=%.2f, Y=%.2f", GetMousePosition().x, GetMousePosition().y), 10, 40, 20, BLUE);
}

int main() {
    constexpr int screen_width = 1200;
    constexpr int screen_height = 800;

    float player_dim = 30;
    float player_x = screen_width/2 - player_dim/2;
    float player_y = screen_height/2 - player_dim/2;

    InitWindow(screen_width, screen_height, "Paint Ball Game");
    SetTargetFPS(60);
    srand(time(NULL));

    while (!WindowShouldClose()) {
        // update game logic should go here

        BeginDrawing();
        ClearBackground(WHITE);
        // everything we want to draw has to be done within Begin/End Drawing
        update_player(player_x, player_y);
        draw_direction(player_x, player_y, player_dim);
        game_info(player_x, player_y);

        DrawRectangle(player_x, player_y, player_dim, player_dim, BLUE);
        // cout<<"Player Coordinates: "<<player_x<<" "<<player_y<<endl;
        // cout<<"User Mouse Coordinates: "<<GetMousePosition().x<<" "<<GetMousePosition().y<<endl;
        EndDrawing();
    }
    CloseWindow();
    return 0;
}