#ifndef GameState_H
#define GameState_H

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include "Game.h"
#include "Collision.h"
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"

class Game;
class GameState;
class MenuState;
class PlayState;
class StoreState;
class BackdoorState;
class TutorialState;

class GameState{
protected:
    float timer;
    float fadeTimer;
    int fadeTransparency;

public:
    // Public variables
    Game* game;

    // Constructor and Destructor
    GameState(): timer(0), fadeTimer(0), fadeTransparency(0) {}
    virtual ~GameState() = default;

    // Loop
    virtual void draw() = 0;
    virtual void update(const float dt) = 0;
    virtual void handle_input() = 0;

    // Other
    virtual void fadeIn(float factor = 1);
    virtual void fadeOut(float factor = 1);
};

/*_____________Menu_____________*/
class MenuState : public GameState{
protected:
    void load_game();
    void load_store();

    std::vector<sf::Text> buttons;
    sf::Text title;
    const int NUM_BUTTONS = 3;

    bool isTextClicked(sf::Text text);
public:
    // Constructor and Destructor
    MenuState(Game* game);

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;
};

/*_____________Play_____________*/
class PlayState : public GameState{
protected:
    float timerInsertAsteroid, timerInsertCoin, timerInsertPlanet;
    float timerCrash, timerOffCourse;
    int rng1, rng2, rng3;
    std::vector<Entity*> entityList;
    std::vector<sf::Text> gameText;
    sf::RectangleShape background;

    void pause_game();
    void setup();

public:
    // Constructor and Destructor
    PlayState(Game* game);
    ~PlayState();

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
    void reset();

    // Collision Detection
    bool collide(Entity* obj);
    bool collide(Obstacle* obj);
    bool collide(Coin* obj);

    // Check if Past Yet
    bool checkPastYet(Entity* obj);
    int checkBadEvent(float dt);

    // Insert
    void insertAsteroid(int rng);
    void insertPlanet(int rng);
    void insertCoin(int rng);
};


/*_____________Store_____________*/
class StoreState : public GameState{
public:
    // Constructor and Destructor
    StoreState(Game* game);
    ~StoreState() = default;

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;
};

/*_____________Event_____________*/
class EventState : public GameState{
private:
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Text textInfo, textInfo2;
    int eventType;
    sf::Font font1;
    sf::Font font2;
    std::vector<sf::Text> choiceButtons;
    bool isTextClicked(sf::Text text);

public:
    // Constructor and Destructor
    EventState(Game* game, int type);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Backdoor_____________*/
class BackdoorState : public PlayState{

public:
    // Constructor and Destructor
    BackdoorState(Game* game, int type);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Tutorial_____________*/
class TutorialState : public PlayState{

public:
    // Constructor and Destructor
    TutorialState(Game* game, int type);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Pause_____________*/
class PauseState : public MenuState{

public:
    // Constructor and Destructor
    PauseState(Game* game): MenuState(game){}

    // Loop
//virtual void handle_input() override;
//virtual void update(const float dt) override;
//virtual void draw() override;
};

/*_____________End_____________*/
class EndState : public MenuState{

public:
    // Constructor and Destructor
    EndState(Game* game): MenuState(game){}

    // Loop

};

#endif // GameState_H



