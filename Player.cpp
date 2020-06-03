#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* objText, sf::Vector2f objPos, float objSpd, int objPass, int objGold, sf::Vector2u aICount)
    : Entity(objText, objPos, objSpd), animation(objText + 3, aICount, 0.005f), passenger(objPass), gold(objGold),
      numRightHit(0), numLeftHit(0){

    // Get left wing
    leftWing.setTexture(*(objText+1));
    leftWing.setPosition(objPos);
    leftWing.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);

    // Get right wing
    rightWing.setTexture(*(objText+2));
    rightWing.setPosition(objPos);
    rightWing.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);

    // Get explosion
    explosion.setTexture(*(objText+3));
    explosion.setPosition(objPos);
    explosion.setOrigin(explosion.getGlobalBounds().width / 2 / 9, explosion.getGlobalBounds().height / 2 / 9);


    // Scale down to right scale
    sf::Vector2f scaleFactor(200 / body.getGlobalBounds().width, 200 / body.getGlobalBounds().height);
    body.scale(scaleFactor);
    leftWing.scale(scaleFactor);
    rightWing.scale(scaleFactor);

    sf::Vector2f scaleFactor2(1800 / explosion.getGlobalBounds().width, 1800 / explosion.getGlobalBounds().height);
    explosion.scale(scaleFactor2);
}

void Player::update(float dt){
    // Lets the ship slow down
    velocity.x *= 0.95f;
    velocity.y *= 0.95f;

    // Update any movement
    if(!isExplode){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            velocity.y -= speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            velocity.y += speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x -= speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += speed;
        // Check for wings
        velocity.x += numRightHit * speed/16;
        velocity.x -= numLeftHit * speed/16;
    }

    // Moves the body
    move();

    // Check for explosion animation
    if(isExplode)
        animation.updateOnce(dt);
    else
        animation.reset();
    explosion.setTextureRect(animation.uvRect);
}

void Player::reset(){
    isExplode = false;
    numRightHit = 0;
    numLeftHit = 0;
    velocity = sf::Vector2f(0,0);
}

void Player::move(){
    body.move(velocity);
    leftWing.move(velocity);
    rightWing.move(velocity);
    explosion.move(velocity);
}

void Player::draw(sf::RenderWindow& window){
    window.draw(body);
    window.draw(leftWing);
    window.draw(rightWing);

    if(isExplode)
        window.draw(explosion);
}

void Player::setPosition(sf::Vector2f objPos) {
    body.setPosition(objPos);
    leftWing.setPosition(objPos);
    rightWing.setPosition(objPos);
    explosion.setPosition(objPos);
}

void Player::setPosition(float x, float y) {
    body.setPosition(x,y);
    leftWing.setPosition(x,y);
    rightWing.setPosition(x,y);
    explosion.setPosition(x,y);
}
