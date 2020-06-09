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

public:
    //Constructors and Destructor
    Entity() = default;
    Entity(const Entity&) = default;
    Entity& operator =(const Entity&) = default;
    Entity(sf::Texture* text, sf::Vector2f pos, float spd);
    virtual ~Entity() = 0;

    // Window Action
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window){ window.draw(body); }
    virtual void move(){ body.move(velocity); }

    // Getters
    std::string name() const;
    sf::Sprite getBody() const { return body; }
    float getSpeed () const { return speed; }
    sf::Vector2f getVelocity() const { return velocity; }
    sf::Vector2f getPosition() const { return body.getPosition(); }
    sf::FloatRect getGlobalBounds() const { return body.getGlobalBounds(); }

    // Setters
    void setSpeed(float spd) { speed = spd; }
    virtual void setPosition(sf::Vector2f objPos) { body.setPosition(objPos); }
    virtual void setPosition(float x, float y) { body.setPosition(x,y); }
    virtual void setOrigin(sf::Vector2f objPos){ body.setOrigin(objPos); }
    virtual void setOrigin(float x, float y){ body.setOrigin(x,y); }
    virtual void setVelocity(sf::Vector2f objVel);
    virtual void setVelocity(float x, float y);
};

#endif // ENTITY_H
