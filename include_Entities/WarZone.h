#ifndef WARZONE_H
#define WARZONE_H

#include "Entity.h"

class WarZone: public Entity{
protected:
    float rotation;

public:
    // Constructors
    WarZone() = default;
    WarZone(sf::Texture* text, sf::Vector2f pos, float scl = 1);

    // Action
    void healPlayer(Player& player);
    void killPlayer(Player& player);
};

#endif // WARZONE_H
