#ifndef GAME_H
#define GAME_H

#include <Gamestate.h>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

const float VIEW_WIDTH = 2048.0f;
const float VIEW_HEIGHT = 1152.0f;

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

        sf::SoundBuffer buffer;
        sf::Texture playerTexture;
        sf::Texture asteroidTexture;
        sf::View view;
        Player player1;
        Asteroid ast1;
        sf::Sound sound;

        void push_state(Gamestate* state);
        void pop_state();



        void game_loop();

        sf::RenderWindow window;

    private:
        std::vector<Gamestate*> states;
        void setup();
};



#endif // GAME_H
