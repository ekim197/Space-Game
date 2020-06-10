#ifndef GameState_H
#define GameState_H

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Collision.h"
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "WarZone.h"
#include "Resource.h"

class Game;

/*_____________Game_____________*/
class GameState{
protected:
    float timer;
    float fadeTimer;
    int fadeTransparency;

public:
    // Public variables
    Game* game;

    // Constructor and Destructor
    GameState(): timer(0), fadeTimer(0), fadeTransparency(0) { Resource::clickTimer = 0; }
    virtual ~GameState() = default;

    // Loop
    virtual void draw() = 0;
    virtual void update(const float dt) = 0;
    virtual void handle_input() = 0;

    // Other
    virtual bool isTextClicked(sf::Text text);
    virtual void fadeIn(float factor = 1);
    virtual void fadeOut(float factor = 1);
    virtual void timeIncrement(const float dt);
};

/*_____________Menu_____________*/
class MenuState : public GameState{
protected:
    int numButtons;
    std::vector<sf::Text> buttons;
    sf::Text title;

public:
    // Constructor
    MenuState() = default;
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
    float timerAddAsteroid;
    int asteroidPerTime;
    std::vector<Entity*> entityList;
    std::vector<sf::Text> gameText;
    sf::RectangleShape background[2];

public:
    // Public Variables
    Player player;

    // Constructor and Destructor
    PlayState(Game* game, Player& player);
    ~PlayState();

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;

    void updateText(const float dt);
    void reset();

    // Collision Detection
    bool collide(Entity* obj, float dt);
    bool collide(Obstacle* obj);
    bool collide(Coin* obj);
    bool collide(WarZone* obj, float dt);

    // Check if Past Yet
    bool checkPastYet(Entity* obj);
    int checkBadEvent(float dt);

    // Insert
    void insertAsteroid(int rngVal, float distY);
    void insertPlanet(int rngVal, float distY);
    void insertCoin(int rngVal, float distY);
    void insertWarZone(int rngVal, float distY);

    // Other
    void pause_game();
    void setup();
};

/*_____________Backdoor_____________*/
class BackdoorState : public PlayState{
public:
    // Constructor and Destructor
    BackdoorState(Game* game);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Tutorial_____________*/
class TutorialState : public PlayState{
private:
    sf::Text instructions;

public:
    // Constructor and Destructor
    TutorialState(Game* game);

    // Loop
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Store_____________*/
class StoreState : public MenuState{
private:
    std::vector<sf::Text> prices;
    std::vector<sf::Text> playerInfo;

public:
    // Constructor and Destructor
    StoreState(Game* game);
    ~StoreState() = default;

    // Loop
    void handle_input() override;
    void update(const float dt) override;
    void draw() override;
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
private:
    GameState* prevState;

public:
    // Constructor
    PauseState(GameState* prev): prevState(prev){}
    PauseState(Game* game, GameState* prev);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;

    // Action
    virtual bool isTextClicked(sf::Text text);
};

/*_____________End_____________*/
class EndState: public PauseState{
public:
    // Constructor and Destructor
    EndState(Game* game, GameState* prev);

    // Loop
//    virtual void handle_input() override;
//    virtual void update(const float dt) override;
//    virtual void draw() override;
};

/*_____________Event_____________*/
class EventState : public GameState{
private:
    PlayState* prevState;
    sf::RectangleShape background;
    sf::Text textInfo, textInfo2;
	int eventType;
    std::vector<sf::Text> choiceButtons;

public:
    // Constructor and Destructor
    EventState(Game* game, PlayState* prev, int type);
	enum evTypes {blank, asteroid, lastMember, veer };
    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Outcome_____________*/
class OutcomeState : public GameState {
private:
	PlayState* prevState;
	sf::RectangleShape background;
	sf::Text textInfo, textInfo2;
	std::vector<sf::Text> choiceButtons;
	int outcomeType;

public:
	int eventType;
	enum ocTypes { astSuccess, astSuccess2, astFail, lastSuccess, lastFail, veerSuccess, veerSuccess2, veerFail };

	// Constructor and Destructor
	OutcomeState(Game* game, PlayState* prev, int type);

	// Loop
	virtual void handle_input() override;
	virtual void update(const float dt) override;
	virtual void draw() override;
};

#endif // GameState_H
