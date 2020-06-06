#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u iCount, float swTime)
    : imageCount(iCount), currentImage(0,0), totalTime(0), switchTime(swTime){
    // Set the uvRect
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(float dt, bool isLoop){
    // Increment time
    totalTime += dt;

    // Update currentImage
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

    //set uvRect
    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * uvRect.width;
}

void Animation::reset(){
        currentImage.x = 0;
        currentImage.y = 0;
}
