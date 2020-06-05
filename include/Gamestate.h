#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Obstacle.h"
#include "Coin.h"

class Game;

class Gamestate{
public:
    // Public variables
    Game* game;

    // Constructor and Destructor
    Gamestate() = default;
    virtual ~Gamestate() = default;

    // Loop
    virtual void draw() = 0;
    virtual void update(const float dt) = 0;
    virtual void handle_input() = 0;
};


/*_____________Menu_____________*/
class Menustate : public Gamestate{
private:
    sf::View view;
    void load_game();
    void load_store();

    std::vector<sf::Text> buttons;
    sf::Text title;
    const int NUM_BUTTONS = 3;

    bool isTextClicked(sf::Text text);
public:
    // Constructor and Destructor
    Menustate(Game* game);
    ~Menustate() = default;

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;
};


/*_____________Play_____________*/
class PlayState : public Gamestate{
private:
    float timer1, timer2, timer3;
    int rng1, rng2, rng3;
    std::vector<Entity*> obsList;
    std::vector<sf::Text> gameText;

    void pause_game();
    void setup();

public:
    // Constructor and Destructor
    PlayState(Game* game);
    ~PlayState() = default;

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;

    // Collision Detection
    bool collide(Entity* obj);
    bool collide(Obstacle* obj);
    bool collide(Coin* obj);

    // Check if Past Yet
    bool checkPastYet(Entity* obj);

    // Insert
    void insertAsteroid(int rng);
    void insertPlanet(int rng);
    void insertCoin(int rng);
};


/*_____________Store_____________*/
class StoreState : public Gamestate{
public:
    // Constructor and Destructor
    StoreState(Game* game);
    ~StoreState() = default;

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;
};

#endif // GAMESTATE_H
