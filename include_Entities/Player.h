#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player: public Entity{
protected:
    sf::Sprite leftWing[2];
    sf::Sprite rightWing[2];
    sf::Sprite explosion;
    sf::Sprite mainStatus;
    sf::Sprite leftStatus;
    sf::Sprite rightStatus;
    Animation animation;
    int crew;
    int gold;
    bool isExplode;
	bool isInWarZone;
	bool isSucked;
    float numRightHit;
    float numLeftHit;

public:
    // Constructors
    Player() = default;
    Player(sf::Texture* text, sf::Vector2u aICount, sf::Vector2f pos, float spd, int crw, int gld);
    Player(const Player& obj) = default;
    Player& operator=(const Player& obj) = default;

    // Window Action
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void move(const float dt);
    void moveStatus();

    // Getters
    sf::Sprite getLeftWing() { return leftWing[0]; }
    sf::Sprite getRightWing() { return rightWing[0]; }
    sf::Sprite getExplosion() {return explosion; }
    Animation getAnimation() { return animation; }
    int getCrew() const { return crew; }
    int getGold() const { return gold; }
    bool getIsExplode(){ return isExplode; }
	bool getIsInWarZone() { return isInWarZone;  }
	bool getIsSucked() { return isSucked;  }
    float getNumLeftHit() { return numLeftHit; }
    float getNumRightHit() { return numRightHit; }

    // Setters
    void setCrew(int crw) { crew = crw; }
    void setGold(int gld) { gold = gld; }
    void setNumRightHit(int numHit) { numRightHit = numHit; }
    void setNumLeftHit(int numHit) { numLeftHit = numHit; }
    void setPosition(sf::Vector2f objPos) override;
    void setPosition(float x, float y) override;
    void setStatusPosition(sf::Vector2f objPos);
    void setStatusPosition(float x, float y);
    void setOrigin(sf::Vector2f objPos) override;
    void setOrigin(float x, float y) override;

    // Modifiers
    void gainCrew(int crw = 1) { crew += crw; }
    void loseCrew(int crw = 1) { crew -= crw; }
    void gainGold(int gld = 1) { gold += gld; }
    void loseGold(int gld = 1) { gold -= gld; }
    void moveLeft(){ velocity.x -= speed - numRightHit * speed/600; } // numRightHit makes it harder to move left
    void moveRight(){ velocity.x += speed - numLeftHit * speed/600; } // numLeftHit makes it harder to move right
    void moveUp(){ velocity.y -= speed; }
    void moveDown(){ velocity.y += speed; }

    // Action
    void reset();
    void explode();
	void warZone(){	isInWarZone = true; }
	void unWarZone(){	isInWarZone = false; }
	void sucked();
    void hitLeft(int num = 1);
    void hitRight(int num = 1);
    void healLeft(int num = 1);
    void healRight(int num = 1);
    void colorStatus();
};

#endif // PLAYER_H
