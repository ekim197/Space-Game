#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* text, sf::Vector2u aICount, sf::Vector2f pos, float spd, int crw, int gld)
    : Entity(text, pos, spd), animation(text + 3, aICount, 0.025f), crew(crw), gold(gld), numRightHit(0), numLeftHit(0){
    // Set Textures
    leftWing.setTexture(text[1]);
    rightWing.setTexture(text[2]);
    explosion.setTexture(text[3]);

    // Set Position and Origin
    setPosition(pos);
    setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    explosion.setOrigin(explosion.getGlobalBounds().width / 2 / 9, explosion.getGlobalBounds().height / 2 / 9);

    // Scale down to right scale
    sf::Vector2f scaleFactor(200 / body.getGlobalBounds().width, 200 / body.getGlobalBounds().height);
    sf::Vector2f scaleFactor2(200 * aICount.x / explosion.getGlobalBounds().width, 200 * aICount.y / explosion.getGlobalBounds().height);

    body.scale(scaleFactor);
    leftWing.scale(scaleFactor);
    rightWing.scale(scaleFactor);
    explosion.scale(scaleFactor2);
}

void Player::update(float dt){
    // Slows ship gradually
    velocity.x *= 0.992f;
    velocity.y *= 0.992f;

    // Update Movement if Ship is not Exploded
    if(!isExplode){
        // Key Inputs
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x -= speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += speed;

        // Move if Wings are Hit
        velocity.x += numRightHit * speed/300;
        velocity.x -= numLeftHit * speed/300;

        // Guarentee Ship moves first
        velocity.y -= 1.5 * speed;
    }

    move();

    // Check for explosion animation
    if(isExplode)
        animation.updateOnce(dt);
    else
        animation.reset();
    explosion.setTextureRect(animation.uvRect);
}

void Player::draw(sf::RenderWindow& window){
    window.draw(body);
    window.draw(leftWing);
    window.draw(rightWing);

    if(isExplode)
        window.draw(explosion);
}

void Player::move(){
    body.move(velocity);
    leftWing.move(velocity);
    rightWing.move(velocity);
    explosion.move(velocity);
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

void Player::setOrigin(sf::Vector2f objPos) {
    body.setOrigin(objPos);
    leftWing.setOrigin(objPos);
    rightWing.setOrigin(objPos);
}

void Player::setOrigin(float x, float y) {
    body.setOrigin(x,y);
    leftWing.setOrigin(x,y);
    rightWing.setOrigin(x,y);
}

void Player::reset(){
    isExplode = false;
    numRightHit = 0;
    numLeftHit = 0;
    velocity = sf::Vector2f(0,0);
}
