#include "Entity.h"
#include <iostream>

Entity::Entity(sf::Texture* objText, sf::Vector2f pos, float spd)
    : speed(spd){
    // Body
    body.setTexture(*objText);
    body.setPosition(pos);
    float originX = body.getGlobalBounds().width / 2;
    float originY = body.getGlobalBounds().height / 2;
    body.setOrigin(originX, originY);

    velocity = sf::Vector2f(0,0);
}

std::string Entity::name() const{
    std::string className = typeid(*this).name();
    className = className.substr(className.find_first_not_of("0123456789"));
    return className;
}






