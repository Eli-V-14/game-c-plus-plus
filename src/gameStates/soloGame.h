//
// Created by vanget on 10/17/2025.
//

#ifndef GAME_C_SOLOGAME_H
#define GAME_C_SOLOGAME_H


#include <raylib.h>

#include "gameState.h"
#include "gameStateManager.h"

class SoloGame : public GameState {
private:
    GameStateManager* gsm;
    // add variables
public:
    SoloGame(GameStateManager* gsm) : gsm(gsm) {}
    void init() override {
        // initialize menu resources
    }

    void update(float dt) override {
        // update game logic
    }

    void render() override {
        // render the screen
    }

    void handleInput() override {
        // handle inputs
    }

    ~SoloGame() override {

    }
};



#endif //GAME_C_SOLOGAME_H