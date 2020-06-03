#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gamestate.h"
#include "Collision.h"

using namespace Collision;

PlayState::PlayState(Game* game){
    // Reset Player
    this->game = game;
    timer1 = 2;

    game->player1.setPosition(VIEW_WIDTH/2, game->player1.getPosition().y);
    game->player1.reset();
}

void PlayState::handle_input(){
    sf::Event event;
    while (this->game->window.pollEvent(event)){
        switch (event.type){
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

void PlayState::update(const float dt){
    //Time Stuff
    timer1 += dt;
    if(timer1 >= 2){
        obsList.push_back(new Asteroid(&game->asteroidTexture,
                                       sf::Vector2f(game->rng % 2048, game->player1.getPosition().y - 1300),
                                       sf::Vector2u(4,4),
                                       game->rng % 4, (game->rng / 100) %4,
                                       2));
        timer1 = 0;
    }

;
    game->player1.update(dt);
    game->coin.update(dt);

    for(auto const& i: obsList)
        i->update(dt);

    std::cout << "Size     " <<  obsList.size() << '\n';
    game->planet[2].update(dt);
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, game->player1.getPosition().y - VIEW_HEIGHT/3));

    // Collision detection
    for(auto const& i: obsList)
        collide(i);
    collide(& game->planet[2]);
    collide(& game->coin);
}

void PlayState::draw(){
    // Set Background
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH , VIEW_HEIGHT));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/background_temp2.png");
    background.setTexture(&backgroundTexture);
    background.setOrigin(0, VIEW_HEIGHT);
    background.setPosition(0, 0);

    // Draw Background
    game->window.clear(sf::Color(8,29,49));
    //game->window.draw(background);

    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: obsList)
        i->draw(game->window);
    game->planet[2].draw(game->window);
    game->coin.draw(game->window);

    // Draw Player
    game->player1.draw(game->window);
}

void PlayState::collide(Obstacle* obj){
    // Main body
    if(PixelPerfectTest(game->player1.getBody(), obj->getBody()) && !game->player1.getIsExplode()){
        game->sound.play();
        game->player1.explode();
    }

    // Right Wing Collision detection
    if(PixelPerfectTest(game->player1.getRightWing(), obj->getBody()))
        game->player1.hitRight();
    // Left Wing Collision detection
    if(PixelPerfectTest(game->player1.getLeftWing(), obj->getBody()))
        game->player1.hitLeft();
}

void PlayState::collide(Coin* obj){
    if(PixelPerfectTest(game->player1.getBody(), obj->getBody()))
        game->player1.gainGold();
    if(PixelPerfectTest(game->player1.getRightWing(), obj->getBody()))
        game->player1.gainGold();
    if(PixelPerfectTest(game->player1.getLeftWing(), obj->getBody()))
        game->player1.gainGold();
}

void PlayState::pause_game(){
    game->push_state(new Menustate(game));
}

