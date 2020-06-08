#include "GameState.h"
#include <iostream>

bool GameState::isTextClicked(sf::Text text){
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height + 20);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}

void GameState::fadeIn(float factor){
    sf::RectangleShape fade;
    fade.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    fade.setPosition(game->view.getCenter());
    fade.setOrigin(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    fade.setFillColor(sf::Color(0,0,0, 255 - fadeTransparency));
    if(fadeTransparency < 255)
        fadeTransparency += factor;
    else
        fadeTransparency = 255;
    game->window.draw(fade);
}

void GameState::fadeOut(float factor){
    sf::RectangleShape fade;
    fade.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    fade.setPosition(game->view.getCenter());
    fade.setOrigin(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    fade.setFillColor(sf::Color(0,0,0, 255 - fadeTransparency));
    if(fadeTransparency > 0)
        fadeTransparency -= factor;
    else
        fadeTransparency = 0;
    game->window.draw(fade);
}
