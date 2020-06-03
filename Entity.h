#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <typeinfo.h>
#include <string>
#include "Animation.h"


class Entity{
protected:
    sf::Sprite body;
    float speed;
    sf::Vector2f velocity;
    bool inView;

public:
    //Constructors and Destructors
    Entity() = default;
    Entity(sf::Texture* objText, sf::Vector2f pos, float spd);
    virtual ~Entity(){}

    // Getters
    std::string name() const;                                                       // gets Name of class
    sf::Sprite getBody() const { return body; }                                       // gets Body
    float getSpeed () const { return speed; }                                         // gets Speed
    sf::Vector2f getVelocity() const { return velocity; }                            // gets Velocity
    sf::Vector2f getPosition() const { return body.getPosition(); }                  // gets Position
    sf::FloatRect getGlobalBounds() const { return body.getGlobalBounds(); }         // gets GlobalBounds

    // Setters
    virtual void setPosition(sf::Vector2f objPos) { body.setPosition(objPos); }
    virtual void setPosition(float x, float y) { body.setPosition(x,y); }

    // Other
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window){ window.draw(body); }
};

#endif // ENTITY_H
