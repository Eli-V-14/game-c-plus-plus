//
// Created by vanget on 10/12/2025.
//

#ifndef GAME_C_GAMEMODE_H
#define GAME_C_GAMEMODE_H


#include <raylib.h>

#include "gameState.h"
#include "gameStateManager.h"
#include "soloLobby.h"
#include "../coreMechanics/settings.h"
using namespace std;

class GameType : public GameState {
private:
    GameStateManager* gsm;
    Texture2D backgroundSheet = {};
    int bgNumFrames = 0;
    int currentFrame = 0;
    float frameTime = 0;
    float timer = 0;

    Texture2D startScreenSheet = {};
    Texture2D cautionTape = {};
    float startWidth = 0;
    float startHeight = 0;



    Rectangle source = {};
    Rectangle dest = {};

    BoundingBox solo = {};
    BoundingBox multi = {};
    BoundingBox mouse = {};
public:
    GameType(GameStateManager* gsm) : gsm(gsm) {}
    void init() override {
        // FIX ME
        backgroundSheet = LoadTexture("../images/FIXME.png");
        // FIX ME
        bgNumFrames = 0;
        currentFrame = 0;
        frameTime = 0.2;
        timer = 0.0f;

        startScreenSheet = LoadTexture("../images/type/gameTypeScreen.png");
        startWidth = startScreenSheet.width;
        startHeight = startScreenSheet.height;

        cautionTape = LoadTexture("../images/type/caution.png");


        source = {startWidth, 0, startWidth, startHeight};
        dest = {0, 0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)};

        solo = {{386, 207, 0}, {1537, 449, 0}};
        multi = {{389, 654, 0}, {1537, 893, 0}};

    }

    void update(float dt) override {
        // update game logic
        mouse = {{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), 0},
            {static_cast<float>(GetMouseX() + 2.0), static_cast<float>(GetMouseY() + 2.0), 0}};
    }

    void checkCollisions() {
        if (CheckCollisionBoxes(mouse, solo)) {
            startScreenSheet = LoadTexture("../images/type/soloHover.png");
        } else if (CheckCollisionBoxes(mouse, multi)) {
            startScreenSheet = LoadTexture("../images/type/multiHover.png");
        } else {
            startScreenSheet = LoadTexture("../images/type/gameType.png");
        }
    }

    void render() override {
        ClearBackground(BLACK);

        // FIX ME
        // DrawTexture(backgroundSheet, source, dest, WHITE);

        DrawTexturePro(startScreenSheet, source, dest, {0,0}, 0.0f, WHITE);
        // Used to check mouse location for collisions
        // DrawBoundingBox(solo, GREEN);
        // DrawBoundingBox(multi, GREEN);
        // DrawBoundingBox(mouse, RED);

        checkCollisions();
        DrawTexturePro(cautionTape, source, dest, {0,0}, 0.0f, WHITE);
    }

    void handleInput() override {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionBoxes(mouse, solo)) {
                startScreenSheet = LoadTexture("../images/type/soloClick.png");
                gsm->changeState(new SoloLobby(gsm));
            } else if (CheckCollisionBoxes(mouse, multi)) {
                startScreenSheet = LoadTexture("../images/type/multiClick.png");
            }
        }
    }

    ~GameType() override {

    }
};

#endif //GAME_C_GAMEMODE_H