#include <raylib.h>
#include <cmath>
#include <ctime>
#include "player.h"
#include "mouse.h"
#include "stats.h"
#include "settings.h"
#include "playerCamera.h"

int main() {
    // --- Initialize window ---
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Multiplayer Game");
    SetTargetFPS(FPS);
    srand(time(NULL));

    Player p(0, 0, 30, 50);
    PlayerCamera pCamera(-SCREEN_WIDTH/2 - p.getWidth() / 2, -SCREEN_HEIGHT/2 - p.getHeight() / 2, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    Stats s;
    // Mouse m;

    // --- Main game loop ---
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        p.update(dt, pCamera);
        pCamera.followPlayer(p.getX(), p.getY());

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(WHITE);

        int gridSize = 100; // spacing between lines
        int worldSize = 6000; // total size of the grid (in world units)

        // Draw vertical lines
        for (int x = -worldSize; x <= worldSize; x += gridSize) {
            DrawLine(x - pCamera.camRect.x, -worldSize - pCamera.camRect.y,
                     x - pCamera.camRect.x, worldSize - pCamera.camRect.y, LIGHTGRAY);
        }

        // Draw horizontal lines
        for (int y = -worldSize; y <= worldSize; y += gridSize) {
            DrawLine(-worldSize - pCamera.camRect.x, y - pCamera.camRect.y,
                     worldSize - pCamera.camRect.x, y - pCamera.camRect.y, LIGHTGRAY);
        }


        p.drawPlayer(pCamera.camRect.x, pCamera.camRect.y);
        // m.drawDirection(p.getX(), p.getY(), p.getWidth(), p.getHeight());


        DrawRectangleLines(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
        s.displayStats(p.getX(), p.getY());

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
