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

class SoloGame final : public GameState {
private:
    // add variables
    const int MAX_ENEMIES = 15;

    GameStateManager* gsm;
    PlayerCamera* pc;
    Player* p;
    // Stats* s;

    vector<Enemy> enemies;

    int gridSize = 100;
    int worldSize = 6000;

public:
    explicit SoloGame(GameStateManager* gsm) : gsm(gsm), p(nullptr), pc(nullptr) {}
    void init() override {
        // initialize menu resources
        p = new Player(0,0,30,50);
        pc = new PlayerCamera(-SCREEN_WIDTH / 2 - p->getWidth() / 2,
                            -SCREEN_HEIGHT / 2 - p->getHeight() / 2,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SCREEN_WIDTH, SCREEN_HEIGHT);
        // s = new Stats();

    }
    void generateEnemy(float playerX, float playerY) {
        mt19937 rng(random_device{}());
        uniform_real_distribution<float> distAngle(0.0, 2.0f * PI);
        uniform_real_distribution<float> distRadius(500, 700);
        float angle = distAngle(rng);
        float radius = distRadius(rng);

        enemies.push_back(Enemy(playerX + cosf(angle) * radius,
                                    playerY + sinf(angle) * radius,
                                    30, 50));
    }

    void updateEnemies(float dt, float playerX, float playerY) {
        for (auto& e : enemies) {
            e.update(dt, p->getX(), p->getY(), *pc);
        }

        while (enemies.size() < MAX_ENEMIES) {
            generateEnemy(playerX, playerY);
        }
    }

    static void checkShotCollision(vector<Shoot>& ss, vector<Enemy>& es) {
        for (auto& e : es) {
            for (auto& s : ss) {
                if (CheckCollisionRecs(e.getRect(), s.getRect())) {
                    s.active = false;
                    e.active = false;
                }
            }
        }
        // Remove inactive enemies
        es.erase(remove_if(es.begin(), es.end(), [](const Enemy& e){ return !e.active; }), es.end());
        // Remove inactive shots
        ss.erase(remove_if(ss.begin(), ss.end(), [](const Shoot& s){ return !s.active; }), ss.end());
    }

    void update(float dt) override {
        // update game logic
        p->update(dt, *pc);
        pc->followPlayer(p->getX(), p->getY());
        updateEnemies(dt, p->getX(), p->getY());
    }

    void drawBackgroundLines() const {
        // Get camera info
        float camX = pc->camRect.x;
        float camY = pc->camRect.y;
        float camW = pc->camRect.width;
        float camH = pc->camRect.height;
        int screenW = pc->screenWidth;
        int screenH = pc->screenHeight;

        // The ratio of world-space size to screen-space pixels
        float scaleX = screenW / camW;
        float scaleY = screenH / camH;

        // Convert spacing to screen-space (affected by zoom)
        float screenSpacingX = 100.0 * scaleX;
        float screenSpacingY = 100.0 * scaleY;

        // The camera’s offset within a grid cell (so movement scrolls smoothly)
        float offsetX = fmod(camX * scaleX, screenSpacingX);
        float offsetY = fmod(camY * scaleY, screenSpacingY);


        // Draw vertical lines
        for (float x = -offsetX; x < screenW; x += screenSpacingX) {
            DrawLine(x, 0, x, screenH, GRAY);
        }

        // Draw horizontal lines
        for (float y = -offsetY; y < screenH; y += screenSpacingY) {
            DrawLine(0, y, screenW, y, GRAY);
        }
    }



    void render() override {
        // render the screen
        // Draw vertical lines
        ClearBackground(WHITE);
        drawBackgroundLines();

        p->drawPlayer(pc->camRect.x, pc->camRect.y);
        // m.drawDirection(p.getX(), p.getY(), p.getWidth(), p.getHeight());

        for (auto& e : enemies) {
            e.drawEnemy(*pc);
        }

        checkShotCollision(p->shots, enemies);


        DrawRectangleLines(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
        // s->displayStats(p->getX(), p->getY());
    }

    void handleInput() override {
        // handle inputs

    }

    ~SoloGame() override {
        delete pc;
        delete p;
        // delete s;
    }
};



#endif //GAME_C_SOLOGAME_H