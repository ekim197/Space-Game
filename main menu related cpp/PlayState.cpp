#include "PlayState.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Gamestate.h"
#include "Menustate.h"

PlayState::PlayState(Game* game)
{

    this->game = game;


}

PlayState::~PlayState()
{
    //dtor
}

void PlayState::draw(const float dt)
{
    //let's draw a rectangle to make sure this works.
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(100, 100));
    rect.setSize(sf::Vector2f(100, 100));
    //rect.setFillColor(sf::Color::Green);
    sf::Texture shipTexture;
    shipTexture.loadFromFile("D:/Design/C++ CIS29/Space_Ship_small.png");
    rect.setTexture(&shipTexture);

    sf::RectangleShape background(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("D:/Design/C++ CIS29/background_temp2.png");
    background.setTexture(&backgroundTexture);

    game->window.draw(background);
    game->window.draw(rect);

}

void PlayState::update(const float dt)
{

}

void PlayState::handle_input()
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
                pause_game();
            break;

        default:
            break;
        }
    }


}



void PlayState::pause_game()
{
    game->push_state(new Menustate(game));

}
