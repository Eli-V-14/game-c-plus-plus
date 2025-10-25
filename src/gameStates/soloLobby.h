//
// Created by vanget on 10/16/2025.
//

#ifndef GAME_C_SOLOLOBBY_H
#define GAME_C_SOLOLOBBY_H

#include <raylib.h>

#include "../coreMechanics/settings.h"
#include "gameState.h"
#include "gameStateManager.h"
#include "soloGame.h"


class SoloLobby : public GameState {
private:
    GameStateManager* gsm;
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
    BoundingBox start = {};
public:
    explicit SoloLobby(GameStateManager* gsm) : gsm(gsm) {}
    void init() override {
        // initialize core variables
        lobbySheet = LoadTexture("../images/solo/defaultLobby.png");
        startWidth = lobbySheet.width;
        startHeight = lobbySheet.height;

        source = {startWidth, 0, startWidth, startHeight};
        dest = {0, 0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)};
        start = {{1277, 861, 0}, {1801, 1008, 0}};
    }

    void update(float dt) override {
        // update game logic
        mouse = {{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), 0},
            {static_cast<float>(GetMouseX() + 2.0), static_cast<float>(GetMouseY() + 2.0), 0}};
    }

    void checkCollisions() {
        if (CheckCollisionBoxes(mouse, start)) {
            lobbySheet = LoadTexture("../images/solo/lobbyStartHover.png");
        } else {
            lobbySheet = LoadTexture("../images/solo/defaultLobby.png");
        }
    }

    void render() override {
        // render the screen
        // FIX ME
        // DrawTexture(lobbySheet, source, dest, WHITE);

        DrawTexturePro(lobbySheet, source, dest, {0,0}, 0.0f, WHITE);
        // Used to check mouse location for collisions onto start box
        // DrawBoundingBox(mouse, RED);
        // DrawBoundingBox(start, GREEN);

        checkCollisions();

    }

    void handleInput() override {
        // handle inputs
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionBoxes(mouse, start)) {
                lobbySheet = LoadTexture("../images/solo/lobbyStartClick.png");
                gsm->changeState(new SoloGame(gsm));
            }
        }
    }

    ~SoloLobby() override {

    }
};

#endif //GAME_C_SOLOLOBBY_H