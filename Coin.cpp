#include "Coin.h"

Coin::Coin(sf::Texture* objText, sf::Vector2f objPos, sf::Vector2u imageCount)
    : Entity(objText, objPos, 0), animation(objText, imageCount, 0.03f)
{
    body.setOrigin(body.getGlobalBounds().width /2/imageCount.x , body.getGlobalBounds().height/2/imageCount.y);
}

void Coin::update(float dt){
    animation.update(dt);
    body.setTextureRect(animation.uvRect);
}
