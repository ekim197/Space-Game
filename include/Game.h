#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Resource.h"
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"

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

    // Getter
    float topView() { return view.getCenter().y - Resource::VIEW_HEIGHT/2; };

    // Action
    GameState* current_state();
    void push_state(GameState* state);
    void pop_state(unsigned numStates = 1);
    void backToMainState();
    void game_loop();
};

#endif // GAME_H
