#include "Game.h"
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Collision.h"

Game::Game()
{
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "C++ Joe", sf::Style::Close |
                  sf::Style::Titlebar);

    setup();
    //ctor

}

Game::~Game()
{
    while(!states.empty())
        pop_state();
}

Gamestate* Game::current_state()
{
    if(states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::push_state(Gamestate* state)
{
    states.push_back(state);
}

void Game::pop_state()
{
    states.back();
    delete states.back();
    states.pop_back();
}

void Game::game_loop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (current_state() == nullptr)
            continue;

        //get user input for current game state
        current_state()->handle_input();

        //update anything neccessary
        current_state()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        current_state()->draw(dt);

        window.display();
    }
}

void Game::setup(){
    // Create a View
    view = sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

    // Sound Stuff
    if(!buffer.loadFromFile("resources/Ship_Explosion.wav"))
        std::cout << "Sound failed to load\n";

    sound.setBuffer(buffer);

    // Create Player
    if(!Collision::CreateTextureAndBitmask(playerTexture, "resources/Space_Ship.png"))
        std::cout << "failed to load\n";

    player1 = Player(&playerTexture, sf::Vector2f(1024.0f,700.0f), 1.5);

    // Create Objects
    Collision::CreateTextureAndBitmask(asteroidTexture, "resources/Asteroid1.png");
    ast1 = Asteroid(&asteroidTexture, sf::Vector2f(1000.0f,0.0f), .03);
}
