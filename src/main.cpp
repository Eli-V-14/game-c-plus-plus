//
// Created by vanget on 10/12/2025.
//

#include "coreMechanics/settings.h"
#include "gameStates/gameStateManager.h"
#include "gameStates/mainMenuState.h"

using namespace std;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Game");

    GameStateManager gsm;

    // start with the main menu
    gsm.changeState(new MainMenuState(&gsm));

    while (!WindowShouldClose()) {
        BeginDrawing();
        gsm.update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();
    return 0;
}