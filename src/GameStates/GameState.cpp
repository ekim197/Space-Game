#include "GameState.h"

bool GameState::isTextClicked(sf::Text text){
    float x = text.getPosition().x;
	float y = text.getPosition().y - (game->view.getCenter().y - VIEW_HEIGHT/2);
	float width = text.getGlobalBounds().width;
	float height = text.getGlobalBounds().height;
	sf::IntRect rect(x, y, width, height);
	if (rect.contains(sf::Mouse::getPosition(game->window))){
        return true;
    }
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

void GameState::timeIncrement(const float dt){
    timer += dt;
    fadeTimer += dt;
    Resource::clickTimer += dt;
}

/*
void GameState::textSetup(sf::Text* objText, std::string tStr, sf::Font fType, int tSize, sf::Color tColor, sf::Vector2f pos){
    objText->setString(tStr);
    objText->setFont(fType);
    objText->setCharacterSize(tSize);
    objText->setFillColor(tColor);
    objText->setPosition(pos);
}

void GameState::textSetup(sf::Text* objText, std::string tStr, sf::Font fType, int tSize, sf::Color tColor, float x, float y){
    objText->setString(tStr);
    objText->setFont(fType);
    objText->setCharacterSize(tSize);
    objText->setFillColor(tColor);
    objText->setPosition(x,y);
}
*/
