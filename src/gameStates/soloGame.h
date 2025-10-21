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

class SoloGame : public GameState {
private:
    // add variables
    const int MAX_ENEMIES = 20;

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

    void checkShotCollision(vector<Shoot> ss, vector<Enemy> es) {
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

    void render() override {
        // render the screen
        // Draw vertical lines
        ClearBackground(WHITE);
        for (int x = -worldSize; x <= worldSize; x += gridSize) {
            DrawLine(x - pc->camRect.x, -worldSize - pc->camRect.y,
                     x - pc->camRect.x, worldSize - pc->camRect.y, LIGHTGRAY);
        }

        // Draw horizontal lines
        for (int y = -worldSize; y <= worldSize; y += gridSize) {
            DrawLine(-worldSize - pc->camRect.x, y - pc->camRect.y,
                     worldSize - pc->camRect.x, y - pc->camRect.y, LIGHTGRAY);
        }


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