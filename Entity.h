#ifndef ENTITY_H
#define ENTITY_H

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
    Entity() = default;
    Entity(sf::Texture* objTexture, sf::Vector2f objPosition, float objSpeed);
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

class Player: public Entity{
protected:
    int passenger;
    int gold;
    bool isExplode;

public:
    // Constructors
    Player() = default;
    Player(sf::Texture* objTexture, sf::Vector2f objPosition, float objSpeed, int objPassenger = 1, int objGold = 0);

    // Actions
    void update();
    void explode();
    void unexplode(){isExplode = false;}

    // Getters
    int getPassenger() const { return passenger; }
    int getGold() const { return gold; }
    bool getIsExplode(){ return isExplode; }
};

class Obstacle: public Entity{
protected:
    float rotation;

public:
    // Constructor
    Obstacle() = default;
    Obstacle(sf::Texture* objTexture, sf::Vector2f objPosition, float objSpeed = 0, float objRotation = 0, float objScale = 1)
        :Entity(objTexture, objPosition, objSpeed), rotation(objRotation)
        { body.scale(objScale, objScale); }
};

class Asteroid: public Obstacle{
public:
    // Constructor
    Asteroid() = default;
    Asteroid(sf::Texture* objTexture, sf::Vector2f objPosition, float objRotation)
        :Obstacle(objTexture, objPosition, 0, objRotation){}

    // Action
    void rotate() { body.rotate(rotation); }
};

#endif // ENTITY_H
