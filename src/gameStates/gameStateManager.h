//
// Created by vanget on 10/12/2025.
//

#ifndef GAME_C_GAMESTATEMANAGER_H
#define GAME_C_GAMESTATEMANAGER_H
#include "gameState.h"

class GameStateManager {
    GameState* currentState = nullptr;

public:
    void changeState(GameState* newState) {
        if (currentState) {
            delete currentState;
        }
        currentState = newState;
        currentState->init(); // initialize the new state
    }

    void update(float dt) {
        if (currentState) {
            currentState->handleInput();
            currentState->update(dt);
            currentState->render();
        }
    }
    ~GameStateManager() {
        delete currentState;
    }
};

#endif //GAME_C_GAMESTATEMANAGER_H