#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture* text, sf::Vector2u iCount, sf::Vector2f pos, int iCX , int iCY, float rot, float scl)
    :Entity(text, pos, 0), imageCount(iCount), rotation(rot){
    // Create Image from texture pack
    sf::IntRect uvRect;

    uvRect.width = text->getSize().x / float(iCount.x);
    uvRect.height = text->getSize().y / float(iCount.y);
    uvRect.left = iCX * uvRect.width;
    uvRect.top = iCY * uvRect.height;
    body.setOrigin(uvRect.width / 2, uvRect.height / 2);
    body.setTextureRect(uvRect);

    // Scale Image
    body.scale(scl, scl);
}


