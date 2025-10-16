//
// Created by Eli Vang on 10/12/2025.
//

#ifndef GAME_C_GAMESTATESKELETON_H
#define GAME_C_GAMESTATESKELETON_H

#include <raylib.h>

#include "gameState.h"
#include "gameStateManager.h"

class Skeleton : public GameState {
private:
    GameStateManager* gsm;
    // add variables
public:
    Skeleton(GameStateManager* gsm) : gsm(gsm) {}
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

    ~Skeleton() override {

    }
};


#endif //GAME_C_GAMESTATESKELETON_H