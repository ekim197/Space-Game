#ifndef WARZONE_H
#define WARZONE_H

#include "Entity.h"

class WarZone: public Entity{
public:
    // Constructors
    WarZone() = default;
    WarZone(sf::Texture* text, sf::Vector2f pos, float scl = 1);

    // Action
    void update(float dt);
};

#endif // WARZONE_H
