#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

class Obstacle: public Entity{
protected:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float rotation;

public:
    // Constructor
    Obstacle() = default;
    Obstacle(sf::Texture* objText, sf::Vector2f pos, sf::Vector2u iCount,
             int iCX = 0, int iCY = 0, float rot = 0, float scl = 1);

    // Virtual Inherited Function
    void update(float dt) { body.rotate(dt * rotation); }

    // Select
    void selectImage(int x, int y){
        currentImage.x = x;
        currentImage.y = y;
    }
};




class Asteroid: public Obstacle{
public:
    // Constructor
    Asteroid() = default;
    Asteroid(sf::Texture* objText, sf::Vector2f pos, sf::Vector2u iCount, int iCX = 0, int iCY = 0, float rot = 0, float scl = 1)
        :Obstacle(objText, pos, iCount, iCX, iCY, rot, scl){}
};




class Planet: public Obstacle{
public:
    // Constructor
    Planet() = default;
    Planet(sf::Texture* objText, sf::Vector2f pos, sf::Vector2u iCount, int iCX = 0, int iCY = 0, float rot = 0, float scl = 1)
        :Obstacle(objText, pos, iCount, iCX, iCY, rot, scl){}
};

#endif // OBSTACLE_H
