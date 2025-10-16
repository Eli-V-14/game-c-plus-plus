//
// Created by vanget on 10/16/2025.
//

#ifndef GAME_C_SOLOLOBBY_H
#define GAME_C_SOLOLOBBY_H

#include <raylib.h>

#include "../coreMechanics/settings.h"
#include "gameState.h"
#include "gameStateManager.h"


class SoloLobby : public GameState {
private:
    GameStateManager* gsm;
    Texture2D backgroundSheet = {};
    int bgNumFrames = 0;
    int currentFrame = 0;
    float frameTime = 0;
    float timer = 0;

    Texture2D lobbySheet = {};
    float startWidth = 0;
    float startHeight = 0;

    Rectangle source = {};
    Rectangle dest = {};

    BoundingBox mouse = {};
public:
    SoloLobby(GameStateManager* gsm) : gsm(gsm) {}
    void init() override {

        backgroundSheet = LoadTexture("../images/defaultLobby.png");
        startWidth = backgroundSheet.width;
        startHeight = backgroundSheet.height;

        source = {startWidth, 0, startWidth, startHeight};
        dest = {0, 0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)};
    }

    void update(float dt) override {
        // update game logic
    }

    void render() override {
        // render the screen
        // FIX ME
        // DrawTexture(backgroundSheet, source, dest, WHITE);

        DrawTexturePro(backgroundSheet, source, dest, {0,0}, 0.0f, WHITE);
        // Used to check mouse location for collisions
        // DrawBoundingBox(mouse, RED);

    }

    void handleInput() override {
        // handle inputs
    }

    ~SoloLobby() override {

    }
};

#endif //GAME_C_SOLOLOBBY_H