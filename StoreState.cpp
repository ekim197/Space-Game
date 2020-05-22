#include <iostream>
#include <SFML\Graphics.hpp>
#include "Gamestate.h"

StoreState::StoreState(Game* game)
{
    //ctor
    this->game = game;
}

StoreState::~StoreState()
{
    //dtor
}

void StoreState::draw(const float dt)
{
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/store_temp.png");
    background.setTexture(&backgroundTexture);

    game->window.draw(background);
}

void StoreState::handle_input()
{
sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new Menustate(game));
            break;

        default:
            break;
        }
    }

}

void StoreState::update(const float dt)
{

}
