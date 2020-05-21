#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

class Game;

class Gamestate
{
    public:
        Gamestate();
        virtual ~Gamestate();

        Game* game;
        virtual void draw(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void handle_input() = 0;

    private:
};

#endif // GAMESTATE_H
