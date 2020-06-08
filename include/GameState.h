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
#include "WarZone.h"

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
    int numButtons;
    std::vector<sf::Text> buttons;
    sf::Text title;

    bool isTextClicked(sf::Text text);

public:
    // Constructor
    MenuState(Game* game, int buttonNum);

    // Loop
    virtual void handle_input() override;
    virtual void draw() override;
};

/*_____________Play_____________*/
class PlayState : public GameState{
protected:
    float timerInsertAsteroid, timerInsertCoin, timerInsertPlanet, timerInsertWarZone;
    float timerCrash, timerOffCourse, timerInWarZone;
    std::vector<Entity*> entityList;
    std::vector<sf::Text> gameText;
    sf::RectangleShape background;

    void pause_game();
    void setup();

public:
    // Constructor and Destructor
    PlayState(Game* game, Player& player);
    ~PlayState();

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void update(const float dt, Player& player);
    virtual void draw() override;
    virtual void draw(Player& player);

    void updateText(Player& player);
    void reset(Player& player);

    // Collision Detection
    bool collide(Entity* obj, Player& player, float dt);
    bool collide(Obstacle* obj, Player& player);
    bool collide(Coin* obj, Player& player);
    bool collide(WarZone* obj, Player& player, float dt);

    // Check if Past Yet
    bool checkPastYet(Entity* obj, Player& player);
    int checkBadEvent(float dt, Player& player);

    // Insert
    void insertAsteroid(int rngVal, Player& player);
    void insertPlanet(int rngVal, Player& player);
    void insertCoin(int rngVal, Player& player);
    void insertWarZone(int rngVal, Player& player);
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
    sf::Text textInfo, textInfo2;
    int eventType;
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
    BackdoorState(Game* game);

    // Loop
    //virtual void handle_input() override;

    virtual void update(const float dt) override;
    virtual void update(const float dt, Player& player) override;
    virtual void draw() override;
    virtual void draw(Player& player) override;
};

/*_____________Tutorial_____________*/
class TutorialState : public PlayState{
public:
    // Constructor and Destructor
    TutorialState(Game* game);

    // Loop
    virtual void update(const float dt) override;
    virtual void update(const float dt, Player& player) override;
    virtual void draw() override;
    virtual void draw(Player& player) override;
};

/*_____________MainMenu_____________*/
class MainMenuState : public MenuState{
public:
    // Constructor
    MainMenuState(Game* game);

    // Loop
    virtual void update(const float dt) override;
};

/*_____________Pause_____________*/
class PauseState : public MenuState{
public:
    // Constructor and Destructor
    PauseState(Game* game);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________End_____________*/
class EndState{

public:
    // Constructor and Destructor
    EndState(Game* game){}

    // Loop

};

#endif // GameState_H
