#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

class Obstacle: public Entity{
protected:
    sf::Vector2u imageCount;
    float rotation;

public:
    // Constructors
    Obstacle() = default;
    Obstacle(sf::Texture* text, sf::Vector2u iCount, sf::Vector2f pos,
             int iCX = 0, int iCY = 0, float rot = 0, float scl = 1);

    // Window Action
    void update(float dt) override { body.rotate(dt * rotation); }
};


/*__________Asteroid__________*/
class Asteroid: public Obstacle{
public:
    // Constructors
    Asteroid() = default;
    Asteroid(sf::Texture* text, sf::Vector2u iCount, sf::Vector2f pos, int iCX = 0, int iCY = 0, float rot = 0, float scl = 1)
        :Obstacle(text, iCount, pos, iCX, iCY, rot, scl){}
};


/*__________Planet__________*/
class Planet: public Obstacle{
public:
    // Constructors
    Planet() = default;
    Planet(sf::Texture* text, sf::Vector2u iCount, sf::Vector2f pos, int iCX = 0, int iCY = 0, float rot = 0, float scl = 1)
        :Obstacle(text, iCount, pos, iCX, iCY, rot, scl){}
};

#endif // OBSTACLE_H
