#include "Coin.h"

Coin::Coin(sf::Texture* objText, sf::Vector2u imageCount, sf::Vector2f objPos)
    : Entity(objText, objPos, 0), animation(objText, imageCount, 0.03f){
    // Set Origin
    float originX = body.getGlobalBounds().width /2/imageCount.x;
    float originY = body.getGlobalBounds().height /2/imageCount.y;

    body.setOrigin(originX, originY);
}

void Coin::update(float dt){
    animation.update(dt);
    body.setTextureRect(animation.uvRect);
}
