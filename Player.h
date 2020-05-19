#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player: public Entity{
protected:
    int passenger;
    int gold;

public:
    // Constructors
    Player(sf::Texture *objTexture, sf::Vector2f objPosition, float objSpeed, int objPassenger = 1, int objGold = 0);

    // Actions
    void update();
    void explode();

    // Getters
    int getPassenger() const { return passenger; }
    int getGold() const { return gold; }
};
