#ifndef GameState_H
#define GameState_H

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "Game.h"
#include "Collision.h"
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "WarZone.h"
#include "Resource.h"
#include "Date.h"
#include "Score.h"
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
    bool isTextClicked(sf::Text text);
    void fadeIn(float factor = 1);
    void fadeOut(float factor = 1);
    void timeIncrement(const float dt);
};

/*_____________Menu_____________*/
class MenuState : virtual public GameState{
protected:
    int numButtons;
    std::vector<sf::Text> buttons;
    sf::Text title;

public:
    // Constructor
    MenuState(Game* game, int buttonNum);

    // Loop
    virtual void handle_input() override;
    virtual void draw() override;
};

/*_____________Play_____________*/
class PlayState : virtual public GameState{
protected:
    float timerInsertAsteroid, timerInsertCoin, timerInsertPlanet, timerInsertWarZone;
	float timerCrash, timerSuck, timerOffCourse, timerInWarZone;
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
	bool collide(Planet* obj);
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
    void setup();
};

/*_____________Backdoor_____________*/
class BackdoorState : public PlayState, public MenuState{
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
    sf::Text instruction;
    bool isInstrPass[5];
    float instrTimer[5];

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
    PauseState(Game* game, GameState* prev);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________End_____________*/
class EndState: public MenuState{
private:
    PlayState* prevState;
    std::vector<sf::Text> highScoreText;
    sf::Text name;
    std::string nameStr;
    Score highScore[10];
    bool updateScores;
    bool isNewScoreInserted;

public:
    // Constructor and Destructor
    EndState(Game* game, PlayState* prev);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;

    // Action
    void scoreManage(Score newScore);
};

/*_____________Option_____________*/
class OptionState : public MenuState{
private:
    GameState* prevState;
    std::vector<sf::Text> highScoreText;

public:
    // Constructor
    OptionState(Game* game, GameState* prev);

    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;

    // Other
    void clearBinFile();
    void printBinFile();
};

/*_____________Event_____________*/
class EventState : public GameState{
private:
    PlayState* prevState;
protected:
    sf::RectangleShape background;
    sf::Text textInfo, textInfo2;
	int eventType;
    std::vector<sf::Text> choiceButtons;

public:
    // Constructor and Destructor
    EventState() = default;
    EventState(Game* game, PlayState* prev, int type);
	enum evTypes {blank, asteroid, lastMember, veer, planet };
    // Loop
    virtual void handle_input() override;
    virtual void update(const float dt) override;
    virtual void draw() override;
};

/*_____________Outcome_____________*/
class OutcomeState : public EventState {
private:
    PlayState* prevState;
	int outcomeType;

public:
	// Public Variables
	int eventType;
	enum ocTypes {astSuccess, astSuccess2, astFail, lastSuccess, lastFail, veerSuccess, veerSuccess2,
                  veerFail, veerFail2, suckSuccess, suckFail, suckFail2};

	// Constructor and Destructor
	OutcomeState(Game* game, PlayState* prev, int type);

	// Loop
	virtual void update(const float dt) override;
};

#endif // GameState_H
