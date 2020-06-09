#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

public:
    // Public Variables
    sf::IntRect uvRect;

    // Constructors and Destructor
    Animation() = default;
    Animation(sf::Texture* texture, sf::Vector2u iCount, float swTime);
    ~Animation() = default;

    // Action
    void update(float deltaTime, bool isLoop = 1);
    void updateOnce(float deltaTime){ update(deltaTime, 0); }
    void reset();
};

#endif // ANIMATION_H
