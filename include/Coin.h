#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin: public Entity{
protected:
    Animation animation;

public:
    // Constructors
    Coin() = default;
    Coin(sf::Texture* objText, sf::Vector2u imageCount, sf::Vector2f objPos);

    // Window Action
    void update(float dt);
};

#endif // COIN_H
