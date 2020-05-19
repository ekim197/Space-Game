#include "Player.h"
#include <iostream>

Player::Player(sf::Texture *objTexture, sf::Vector2f objPosition, float objSpeed, int objPassenger, int objGold)
    : Entity(objTexture, objPosition, objSpeed), passenger(objPassenger), gold(objGold){

    sf::Vector2f scaleFactor(200 / body.getGlobalBounds().width, 200 / body.getGlobalBounds().height);
    body.scale(scaleFactor);
}

void Player::update(){
    // Lets the ship slow down
    velocity.x *= 0.99f;
    velocity.y *= 0.99f;

    // Update any movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y += speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;

    // Moves the body
    body.move(velocity);
}

void Player::explode(){
    // Play the explosion audio
    inView = false;
}
