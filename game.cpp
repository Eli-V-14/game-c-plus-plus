//
// Created by Eli Vang on 9/26/2025.
//

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void update_player(int &x, int &y) {
    int normalized = sqrt(50) / 5;
    if (IsKeyDown(KEY_UP) && (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))) {
        y -= normalized;
        x -= normalized;
    }


    if (IsKeyDown(KEY_UP)) y -= 5;
    if (IsKeyDown(KEY_DOWN)) y += 5;
    if (IsKeyDown(KEY_LEFT)) x -= 5;
    if (IsKeyDown(KEY_RIGHT)) x += 5;
}

int main() {
    constexpr int screen_width = 800;
    constexpr int screen_height = 800;

    int player_dim = 30;
    int player_x = screen_width/2 - player_dim/2;
    int player_y = screen_height/2 - player_dim/2;

    InitWindow(screen_width, screen_height, "Paint Ball Game");
    SetTargetFPS(60);
    srand(time(NULL));

    while (!WindowShouldClose()) {
        // update game logic should go here

        BeginDrawing();
        ClearBackground(WHITE);
        // everything we want to draw has to be done within Begin/End Drawing
        update_player(player_x, player_y);

        DrawRectangle(player_x, player_y, player_dim, player_dim, BLUE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
