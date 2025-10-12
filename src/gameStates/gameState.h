//
// Created by vanget on 10/12/2025.
//

#ifndef GAME_C_GAMESTATE_H
#define GAME_C_GAMESTATE_H


class GameState {
    public:
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void handleInput() = 0;
    virtual ~GameState() {}
};


#endif //GAME_C_GAMESTATE_H