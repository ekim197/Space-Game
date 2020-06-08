#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Resource.h"

const float VIEW_WIDTH = 2048.0;
const float VIEW_HEIGHT = 1152.0;
const std::string RESOURCE_PATH = "resources/";

class GameState;

class Game{
private:
    std::vector<GameState*> states;

    void setup();

public:
    // Public Variables
    sf::RenderWindow window;
    sf::View view;
    Player defaultPlayer;
    Player gamePlayer;

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
