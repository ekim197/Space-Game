#include "Entity.h"
#include <iostream>

Entity::Entity(sf::Texture* objTexture, sf::Vector2f objPosition, float objSpeed)
    : speed(objSpeed){
    // Body
    body.setTexture(*objTexture);
    body.setPosition(objPosition);
    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);

    velocity = sf::Vector2f(0.0f,0.0f);
}

Entity::~Entity(){}

std::string Entity::name() const{
    std::string className = typeid(*this).name();
    className = className.substr(className.find_first_not_of("0123456789"));
    return className;
}
