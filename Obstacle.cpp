#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(sf::Texture* objText, sf::Vector2f pos, sf::Vector2u iCount, int iCX , int iCY, float rot, float scl)
    :Entity(objText, pos, 0), imageCount(iCount), rotation(rot)
{
    sf::IntRect uvRect;
    body.scale(scl, scl);
    uvRect.width = objText->getSize().x / float(iCount.x);
    uvRect.height = objText->getSize().y / float(iCount.y);
    uvRect.left = iCX * uvRect.width;
    uvRect.top = iCY * uvRect.height;

    body.setOrigin(uvRect.width / 2, uvRect.height / 2);
    body.setTextureRect(uvRect);
}
