#include "Game.h"
#include <vector>
#include <SFML\Graphics.hpp>

Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "C++ Joe", sf::Style::Close |
                  sf::Style::Titlebar);

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
