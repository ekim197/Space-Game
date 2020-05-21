#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML\Graphics.hpp>
#include "Gamestate.h"

class Menustate : public Gamestate
{
    public:
        Menustate(Game* game);
        virtual ~Menustate();

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handle_input();

    private:
        sf::View view;
        void load_game();
        void load_store();

        std::vector<sf::Text> buttons;
        sf::Font font;
        const int NUM_BUTTONS = 3;

        bool isTextClicked(sf::Text text);
};

#endif // MENUSTATE_H
