#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

class Game;

// Whole Game
class Gamestate
{
    public:
        Gamestate(){}
        virtual ~Gamestate(){};

        Game* game;
        virtual void draw(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void handle_input() = 0;

    private:
};

// Menu
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

// Play
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
        void setup();
};

// Store
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

#endif // GAMESTATE_H
