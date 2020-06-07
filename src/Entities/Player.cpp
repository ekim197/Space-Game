#include "Player.h"

Player::Player(sf::Texture* text, sf::Vector2u aICount, sf::Vector2f pos, float spd, int crw, int gld)
    : Entity(text, pos, spd), animation(text + 8, aICount, 0.025f), crew(crw), gold(gld), numRightHit(0), numLeftHit(0){
    // Set Textures
    leftWing[0].setTexture(text[1]);
    rightWing[0].setTexture(text[2]);
    leftWing[1].setTexture(text[3]);
    rightWing[1].setTexture(text[4]);
    mainStatus.setTexture(text[5]);
    leftStatus.setTexture(text[6]);
    rightStatus.setTexture(text[7]);
    explosion.setTexture(text[8]);

    // Set Position and Origin
    setPosition(pos);
    setStatusPosition(9.0 / 10.0 * 2000.0, pos.y);
    setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    explosion.setOrigin(explosion.getGlobalBounds().width / 2 / 9, explosion.getGlobalBounds().height / 2 / 9);

    // Scale down to right scale
    sf::Vector2f scaleFactor(200 / body.getGlobalBounds().width, 200 / body.getGlobalBounds().height);
    sf::Vector2f scaleFactor2(200 * aICount.x / explosion.getGlobalBounds().width, 200 * aICount.y / explosion.getGlobalBounds().height);

    body.scale(scaleFactor);
    leftWing[0].scale(scaleFactor);
    rightWing[0].scale(scaleFactor);
    leftWing[1].scale(scaleFactor);
    rightWing[1].scale(scaleFactor);
    mainStatus.scale(scaleFactor);
    leftStatus.scale(scaleFactor);
    rightStatus.scale(scaleFactor);
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
            velocity.x -= speed - numRightHit * speed/600;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += speed - numLeftHit * speed/600;

        // Move if Wings are Hit
        velocity.x += numRightHit * speed/300;
        velocity.x -= numLeftHit * speed/300;

        // Guarentee Ship moves first
       velocity.y -= 1.25 * speed;
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
    // Main Body
    window.draw(body);

    // Wings
    if(numLeftHit < 100)
        window.draw(leftWing[0]);
    else
        window.draw(leftWing[1]);
    if(numRightHit < 100)
        window.draw(rightWing[0]);
    else
        window.draw(rightWing[1]);

    // Status
    window.draw(mainStatus);
    window.draw(leftStatus);
    window.draw(rightStatus);

    if(isExplode)
        window.draw(explosion);
}

void Player::move(){
    body.move(velocity);
    leftWing[0].move(velocity);
    rightWing[0].move(velocity);
    leftWing[1].move(velocity);
    rightWing[1].move(velocity);
    explosion.move(velocity);

    mainStatus.move(0, velocity.y);
    leftStatus.move(0, velocity.y);
    rightStatus.move(0, velocity.y);
}

void Player::setPosition(sf::Vector2f objPos) {
    body.setPosition(objPos);
    leftWing[0].setPosition(objPos);
    rightWing[0].setPosition(objPos);
    leftWing[1].setPosition(objPos);
    rightWing[1].setPosition(objPos);
    explosion.setPosition(objPos);
}

void Player::setPosition(float x, float y) {
    body.setPosition(x,y);
    leftWing[0].setPosition(x,y);
    rightWing[0].setPosition(x,y);
    leftWing[1].setPosition(x,y);
    rightWing[1].setPosition(x,y);
    explosion.setPosition(x,y);
}

void Player::setStatusPosition(sf::Vector2f objPos) {
    mainStatus.setPosition(objPos);
    leftStatus.setPosition(objPos);
    rightStatus.setPosition(objPos);
}

void Player::setStatusPosition(float x, float y) {
    mainStatus.setPosition(x,y);
    leftStatus.setPosition(x,y);
    rightStatus.setPosition(x,y);
}

void Player::setOrigin(sf::Vector2f objPos) {
    body.setOrigin(objPos);
    leftWing[0].setOrigin(objPos);
    rightWing[0].setOrigin(objPos);
    leftWing[1].setOrigin(objPos);
    rightWing[1].setOrigin(objPos);
    mainStatus.setOrigin(objPos);
    leftStatus.setOrigin(objPos);
    rightStatus.setOrigin(objPos);
}


void Player::setOrigin(float x, float y) {
    body.setOrigin(x,y);
    leftWing[0].setOrigin(x,y);
    rightWing[0].setOrigin(x,y);
    leftWing[1].setOrigin(x,y);
    rightWing[1].setOrigin(x,y);
    mainStatus.setOrigin(x,y);
    leftStatus.setOrigin(x,y);
    rightStatus.setOrigin(x,y);
}

void Player::reset(){
    isExplode = false;
    numRightHit = 0;
    numLeftHit = 0;
    velocity = sf::Vector2f(0,0);
    mainStatus.setColor(sf::Color::White);
    leftStatus.setColor(sf::Color::White);
    rightStatus.setColor(sf::Color::White);
}

void Player::explode(){
    isExplode = true;
    mainStatus.setColor(sf::Color::Red);
}

void Player::hitLeft() {
    numLeftHit++;
    colorStatus();
}

void Player::hitRight() {
    numRightHit++;
    colorStatus();
}

void Player::healLeft() {
    if(numLeftHit > 0)
        numLeftHit-= 0.1;
    colorStatus();
}

void Player::healRight() {
    if(numRightHit > 0)
        numRightHit-= 0.1;
    colorStatus();
}

void Player::colorStatus(){
    // Left
    float colorShift = numLeftHit * 1.5;
    if(colorShift > 255)
        colorShift = 255;
    else if(colorShift < 0)
        colorShift = 0;
    leftStatus.setColor(sf::Color(255, 255 - colorShift, 255 - colorShift));

    // Right
    colorShift = numRightHit * 1.5;
    if(colorShift > 255)
        colorShift = 255;
    else if(colorShift < 0)
        colorShift = 0;
    rightStatus.setColor(sf::Color(255 , 255 - colorShift, 255 - colorShift));
}
