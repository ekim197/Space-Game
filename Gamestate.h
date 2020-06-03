#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Obstacle.h"
#include "Coin.h"

class Game;

// Whole Game
class Gamestate
{
    public:
        Gamestate(){}
        virtual ~Gamestate(){};

        Game* game;
        virtual void draw() = 0;
        virtual void update(const float dt) = 0;
        virtual void handle_input() = 0;

    private:
};

// Menu
class Menustate : public Gamestate
{
    public:
        Menustate(Game* game);
        ~Menustate() = default;

        void handle_input();
        void update(const float dt);
        void draw();

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
    float timer1;
    std::vector<Obstacle*> obsList;

    public:
        PlayState(Game* game);
        ~PlayState() = default;

        void handle_input();
        void update(const float dt);
        void draw();
        void collide(Obstacle* obj);
        void collide(Coin* obj);

    private:
        void pause_game();
        void setup();

};

// Store
class StoreState : public Gamestate
{
    public:
        StoreState(Game* game);
        ~StoreState() = default;

        void handle_input();
        void update(const float dt);
        void draw();

    private:
};

#endif // GAMESTATE_H
