#pragma once
#include <SFML/Graphics.hpp>
#include <typeinfo.h>
#include <string>

class Entity{
protected:
    sf::Sprite body;
    float speed;
    sf::Vector2f velocity;
    bool inView;

public:
    //Constructors and Destructors
    Entity(sf::Texture *objTexture, sf::Vector2f objPosition, float objSpeed);
    virtual ~Entity() = 0;

    // Getters
    std::string name() const;                                                       // gets Name of class
    sf::Sprite getBody() const { return body; }                                           // gets Body
    float getSpeed () const { return speed; }                                         // gets Speed
    sf::Vector2f getVelocity() const { return velocity; }                            // gets Velocity
    sf::Vector2f getPosition() const { return body.getPosition(); }                  // gets Position
    sf::FloatRect getGlobalBounds() const { return body.getGlobalBounds(); }         // gets GlobalBounds

    //Other
    void draw(sf::RenderWindow& window){ window.draw(body); }
};
