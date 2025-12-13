//
// Created by vanget on 10/17/2025.
//

#ifndef GAME_C_SOLOGAME_H
#define GAME_C_SOLOGAME_H


#include <random>
#include <raylib.h>

#include "gameState.h"
#include "gameStateManager.h"
#include "../coreMechanics/player.h"
#include "../coreMechanics/stats.h"
#include "../coreMechanics/settings.h"
#include "../coreMechanics/playerCamera.h"
#include "../coreMechanics/enemy.h"
#include "../coreMechanics/sword.h"

class SoloGame final : public GameState {
private:
    // add variables
    GameStateManager* gsm;
    PlayerCamera* pc;
    Player*p;
    Stats* stats;
    vector<Rectangle> collidableTiles;


    int gridSize = 250;
    int worldSize = 6000;

    vector<vector<int>> mapGrid;
    Texture2D tileTextures[14];
    const char* tileFiles[14] = {"grass-t", "grass-b", "north", "east", "south", "west", "nve", "nvw", "sve", "svw", "nce", "ncw", "sce", "scw"};
    const int TILE_SRC_SIZE = 64;



public:
    explicit SoloGame(GameStateManager* gsm) : gsm(gsm), p(nullptr), pc(nullptr) {}
    void init() override {
        // initialize menu resources
        p = new Player(15 * gridSize,4 * gridSize,30,50);
        pc = new PlayerCamera(-SCREEN_WIDTH / 2 - p->getWidth() / 2,
                            -SCREEN_HEIGHT / 2 - p->getHeight() / 2,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SCREEN_WIDTH, SCREEN_HEIGHT);
        p->equipWeapon(new Sword(pc->camRect.x, pc->camRect.y + 50));
        stats = new Stats();

        for (int i = 0; i < 14; i++) {
            string path = "../images/map/" + string(tileFiles[i]) + ".png";
            tileTextures[i] = LoadTexture(path.c_str());
        }

        mapGrid = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 2, 2, 2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 7, 2, 2, 2, 2,11, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,10, 2, 2, 2, 6, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 7, 2,11, 1, 1, 1, 1, 1,12, 4, 4, 4,13, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1,10, 6, 0, 0, 9,13, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1,10, 2, 2, 2,11, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 9, 4, 4, 4, 4,13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,12, 4, 8, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
        generateCollidableTiles();

    }

    void checkPlayerCollision() {
        for (const auto& tileRect : collidableTiles) {
            p->resolveCollision(tileRect);
        }
    }

    void update(float dt) {
        // update game logic
        p->update(dt, *pc);
        checkPlayerCollision();
        pc->followPlayer(p->getX(), p->getY());
    }

    void generateCollidableTiles() {
        collidableTiles.clear();
        for (int y = 0; y < mapGrid.size(); y++) {
            for (int x = 0; x < mapGrid[y].size(); x++) {
                int tile = mapGrid[y][x];
                if (tile != 1) { // Only solid tiles
                    Rectangle rect;
                    rect.x = x * gridSize;
                    rect.y = y * gridSize;
                    rect.width = gridSize;
                    rect.height = gridSize;
                    collidableTiles.push_back(rect);
                }
            }
        }
    }


    void drawMapGrid() const {
        for (int y = 0; y < mapGrid.size(); y++) {
            for (int x = 0; x < mapGrid[y].size(); x++) {

                int tile = mapGrid[y][x];
                if (tile < 0 || tile > 13) continue;

                // World position of the tile
                float worldX = x * gridSize;
                float worldY = y * gridSize;

                // Convert to screen-space relative to camera top-left
                float screenX = worldX - pc->camRect.x;
                float screenY = worldY - pc->camRect.y;

                // Draw scaled tile
                DrawTexturePro(
                    tileTextures[tile],
                    {0.0f, 0.0f, (float)TILE_SRC_SIZE, (float)TILE_SRC_SIZE},
                    {screenX, screenY, (float)gridSize, (float)gridSize},
                    {0.0f, 0.0f}, 0.0f, WHITE
                );

                if (tile != 1) {
                    DrawRectangleLines(
                    (int)screenX,
                    (int)screenY,
                    gridSize,
                    gridSize,
                    {0,0, 0, 0}
                    // BLACK // Color of the bounding box
                );
                }
            }
        }
    }



    void render() override {
        // render the screen
        ClearBackground(WHITE);
        drawMapGrid();


        p->drawPlayer(pc->camRect.x, pc->camRect.y);
        // m.drawDirection(p.getX(), p.getY(), p.getWidth(), p.getHeight());

        DrawRectangleLines(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
        stats->displayStats(p->getX(), p->getY());
    }

    void handleInput() override {
        // handle inputs

    }

    ~SoloGame() override {
        delete pc;
        delete p;
        delete stats;

        for (int i = 0; i < 14; i++) {
            UnloadTexture(tileTextures[i]);
        }
    }
};



#endif //GAME_C_SOLOGAME_H