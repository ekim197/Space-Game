#include "GameState.h"

using namespace Resource;

StoreState::StoreState(Game* game){
    // Set Game
    this->game = game;
}

void StoreState::draw(){
    // Background
    game->window.clear();
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    background.setTexture(&backgroundTexture[2]);

    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    game->view.setCenter(view.getCenter());
    game->window.setView(view);

    // Backgrounds
    game->window.draw(background);

    // Buttons

    // Fade
    if(fadeTimer < 3)
        fadeIn(5);
}

void StoreState::handle_input(){
    sf::Event event;

    while (this->game->window.pollEvent(event)){
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new MainMenuState(game));
            break;

        default:
            break;
        }
    }
}

void StoreState::update(const float dt){
    fadeTimer += dt;

}