#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin: public Entity{
    Animation animation;

public:
    Coin() = default;
    Coin(sf::Texture* objText, sf::Vector2f objPos, sf::Vector2u imageCount);
    void update(float dt);
};

#endif // COIN_H
