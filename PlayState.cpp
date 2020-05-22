#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gamestate.h"
#include "Collision.h"

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
    // Set Background
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/background_temp2.png");
    background.setTexture(&backgroundTexture);

    game->window.clear();
    game->window.draw(background);

    game->window.setView(game->view);
    game->ast1.draw(game->window);
    game->player1.draw(game->window);
}

void PlayState::update(const float dt)
{
    game->player1.update();
    game->ast1.rotate();
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, game->player1.getPosition().y - VIEW_HEIGHT/3));

    // Collision detection
    if(Collision::PixelPerfectTest(game->player1.getBody(), game->ast1.getBody()) && !game->player1.getIsExplode()){
        game->sound.play();
        game->player1.explode();
        std::cout << "Collision detected\n";
    }
    else if(!Collision::PixelPerfectTest(game->player1.getBody(), game->ast1.getBody()) && game->player1.getIsExplode())
        game->player1.unexplode();
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

