#include "Entity.h"

Entity::Entity(sf::Texture* texture, sf::Vector2f size, float spd, bool isBg){
    speed = spd;
    velocity = sf::Vector2f(0.0f,0.0f);
    body.setSize(size);
    body.setOrigin( body.getSize() / 2.0f);
    body.setPosition(1024.0f,700.0f);
    body.setTexture(texture);
}

void Entity::update(){
    velocity.x *= 0.98f;
    velocity.y *= 0.98f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y += speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;


    body.move(velocity);
}
