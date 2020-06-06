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

const float VIEW_WIDTH = 2048.0;
const float VIEW_HEIGHT = 1152.0;

class Gamestate;

class Game{
private:
    std::vector<Gamestate*> states;
    void setup();

public:
    // Public Variables
    Gamestate* current_state();
    // Textures, Buffers, and Fonts
    sf::SoundBuffer buffer;
    sf::Texture playerTexture[4];
    sf::Texture asteroidTexture;
    sf::Texture planetTexture;
    sf::Texture coinTexture;
    sf::Font font[3];
    //Window and View
    sf::RenderWindow window;
    sf::View view;
    //Objects
    Player player1;
    // Sound
    sf::Sound sound;
    sf::Music music[2];
    // Time stuff
    long long int rng;

    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Action
    void push_state(Gamestate* state);
    void pop_state();
    void game_loop();
};

#endif // GAME_H
