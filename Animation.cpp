#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u iCount, float swTime){
    imageCount = iCount;
    switchTime = swTime;
    totalTime = 0;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(float deltaTime, bool isLoop){
    totalTime += deltaTime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;

        currentImage.x++;
        if(currentImage.x >= imageCount.x){
            currentImage.x = 0;
            currentImage.y++;
        }
        if(currentImage.y >= imageCount.y && isLoop == 1)
            reset();
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * uvRect.width;
}

void Animation::updateOnce(float deltaTime){
    update(deltaTime, 0);
}

void Animation::reset(){
        currentImage.x = 0;
        currentImage.y = 0;
}
