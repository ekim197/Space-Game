#ifndef GAME_H
#define GAME_H

#include <Gamestate.h>
#include <vector>
#include <SFML\Graphics.hpp>

class Gamestate;

/*
in main.cpp
    Game game;
    game.push_state(new Menustate(&game));
    game.game_loop();
*/

class Game
{
    public:
        Game();
        virtual ~Game();

        Gamestate* current_state();

        void push_state(Gamestate* state);
        void pop_state();



        void game_loop();

        sf::RenderWindow window;

    private:
        std::vector<Gamestate*> states;
};

#endif // GAME_H
