#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player: public Entity{
protected:
    sf::Sprite leftWing;
    sf::Sprite rightWing;
    sf::Sprite explosion;
    Animation animation;
    int passenger;
    int gold;
    bool isExplode;
    int numRightHit;
    int numLeftHit;

public:
    // Constructors
    Player(){};
    Player(sf::Texture* objText, sf::Vector2f objPos, float objSpd, int objPass, int objGold, sf::Vector2u aICount);

    // Actions
    void update(float dt);
    void explode(){ isExplode = true; }
    void reset();
    void hitRight(){ numRightHit += 1; }
    void hitLeft(){ numLeftHit += 1; }
    void move();
    void draw(sf::RenderWindow& window);

    // Getters
    int getPassenger() const { return passenger; }
    int getGold() const { return gold; }
    bool getIsExplode(){ return isExplode; }
    int getNumRightHit() { return numRightHit; }
    int getNumLeftHit() { return numLeftHit; }
    float getSpeed() { return speed; }
    sf::Sprite getRightWing() { return rightWing; }
    sf::Sprite getLeftWing() { return leftWing; }

    // Setters
    void setGold(int g) { gold = g; }
    void setPassenger(int p) { passenger = p; }
    void setSpeed(float s) { speed = s; }
    void setPosition(sf::Vector2f objPos);
    void setPosition(float x, float y);

    // Modifiers
    void gainPassenger(int p = 1) { passenger += p; }
    void gainGold(int g = 1) { gold += g; }
    void losePassenger(int p = 1) { passenger -= p; }
    void loseGold(int g = 1) { gold -= g; }
};

#endif
