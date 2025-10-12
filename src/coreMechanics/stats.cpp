//
// Created by vanget on 10/6/2025.
//

#include <raylib.h>
#include "stats.h"

void Stats::displayStats(float player_x, float player_y) {
    DrawFPS(10,70);
    DrawText(TextFormat("Player Position: X=%.2f, Y=%.2f", player_x, player_y), 10, 10, 20, BLUE);
    DrawText(TextFormat("Mouse Position: X=%.2f, Y=%.2f", GetMouseX(), GetMouseY()), 10, 40, 20, BLUE);
}