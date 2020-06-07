#include "Entity.h"

Entity::Entity(sf::Texture* text, sf::Vector2f pos, float spd)
    : speed(spd), velocity(0,0){
    // Set Texture
    body.setTexture(*text);

    // Set Position and Origin
    setPosition(pos);
    float originX = body.getGlobalBounds().width / 2;
    float originY = body.getGlobalBounds().height / 2;
    setOrigin(originX, originY);
}

Entity::~Entity(){}

std::string Entity::name() const{
    std::string className = typeid(*this).name();
    className = className.substr(className.find_first_not_of("0123456789"));
    return className;
}






