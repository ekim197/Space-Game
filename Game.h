#ifndef GAME_H
#define GAME_H

#include <Gamestate.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"

const float VIEW_WIDTH = 2048.0f;
const float VIEW_HEIGHT = 1152.0f;

class Gamestate;

class Game
{
    public:
        Game();
        virtual ~Game();

        Gamestate* current_state();

        // Textures and buffers

        sf::SoundBuffer buffer;
        sf::Texture playerTexture[4];
        sf::Texture asteroidTexture;
        sf::Texture planetTexture;
        sf::Texture coinTexture;

        //Window and View
        sf::RenderWindow window;
        sf::View view;



        //Objects
        Player player1;
        Asteroid asteroid[4][4];
        Planet planet[4];
        Coin coin;

        sf::Sound sound;

        // Time stuff
        long long int rng;

        void push_state(Gamestate* state);
        void pop_state();
        void game_loop();

    private:
        std::vector<Gamestate*> states;
        void setup();
};

#endif // GAME_H
