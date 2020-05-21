#ifndef STORESTATE_H
#define STORESTATE_H

#include <SFML\Graphics.hpp>
#include "Gamestate.h"
class StoreState : public Gamestate
{
    public:
        StoreState(Game* game);
        virtual ~StoreState();

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handle_input();

    private:
};

#endif // STORESTATE_H
