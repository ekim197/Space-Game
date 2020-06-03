#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation{
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

public:
    Animation(){}
    Animation(sf::Texture* texture, sf::Vector2u iCount, float swTime);
    ~Animation(){}

    sf::IntRect uvRect;


    void update(float deltaTime, bool isLoop = 1);
    void updateOnce(float deltaTime);
    void reset();
};

#endif // ANIMATION_H
