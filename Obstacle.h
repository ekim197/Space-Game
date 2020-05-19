#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Obstacle: public Entity{
protected:
    float rotation;

public:
    // Constructor
    Obstacle(sf::Texture* objTexture, sf::Vector2f objPosition, float objSpeed = 0, float objRotation = 0, float objScale = 1)
        :Entity(objTexture, objPosition, objSpeed), rotation(objRotation)
        { body.scale(objScale, objScale); }
};

class Asteroid: public Obstacle{
public:
    // Constructor
    Asteroid(sf::Texture* objTexture, sf::Vector2f objPosition, float objRotation)
        :Obstacle(objTexture, objPosition, 0, objRotation){}

    // Action
    void rotate() { body.rotate(rotation); }
};
