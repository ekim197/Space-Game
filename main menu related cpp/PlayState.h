#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SFML\Graphics.hpp>
#include "Gamestate.h"
class PlayState : public Gamestate
{
    public:
        PlayState(Game* game);
        virtual ~PlayState();

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handle_input();

    private:
        void pause_game();
};

#endif // PLAYSTATE_H
