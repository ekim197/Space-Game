#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Collision.h"
#include "Sound_.h"

const float VIEW_WIDTH = 2048.0;
const float VIEW_HEIGHT = 1152.0;

class GameState;

class Game{
private:
    std::vector<GameState*> states;

    void setup();

public:
    // Public Variables
    // Textures, Buffers, and Fonts
    sf::SoundBuffer buffer;
    sf::Texture playerTexture[9];
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
    GameState* current_state();
    void push_state(GameState* state);
    void pop_state();
    void game_loop();
    void makeCollisionTexture(sf::Texture& text, std::string file);
    void makeTexture(sf::Texture& text, std::string file);
    void makeFont(sf::Font& font, std::string file);
};

#endif // GAME_H
