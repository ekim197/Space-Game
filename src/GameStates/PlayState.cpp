#include "GameState.h"
#include <sstream>
#include <iomanip>

using namespace Collision;
using namespace Resource;

PlayState::PlayState(Game* game, Player& player)
    : timerInsertAsteroid(0), timerInsertCoin(0), timerInsertPlanet(0), timerCrash(0), timerOffCourse(0), timerInWarZone(0){
    // Push Game
    this->game = game;

    // Reset Player1
    player.setPosition(VIEW_WIDTH/2, player.getPosition().y);
    player.reset();

    // Text Stuff
    sf::Text tempText;
    tempText.setFont(font[0]);
    tempText.setCharacterSize(30);
    tempText.setFillColor(sf::Color::White);

    for(auto i = 0; i < 4; i++){
        gameText.push_back(tempText);
        gameText[i].setPosition(VIEW_WIDTH - 500 , player.getPosition().y - VIEW_HEIGHT * 8/10 + i * 50);
    }
}

PlayState::~PlayState(){
    for(auto key: entityList)
        delete key;
    entityList.clear();
}

void PlayState::handle_input(){
    sf::Event event;
    while (this->game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;
        // Pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new PauseState(game));
            break;
        default:
            break;
        }
    }
}

void PlayState::update(const float dt){
    update(dt, game->player1);
}

void PlayState::update(const float dt, Player& player){
    // Three second delay before things start spawning in
    timer += dt;
    fadeTimer += dt;

    if(timer > 3){
        // Time
        timerInsertAsteroid += dt;
        timerInsertCoin += dt;
        timerInsertPlanet += dt;
        timerInsertWarZone += dt;

        // Insert Entities
        if(timerInsertAsteroid >= 0.5)
            insertAsteroid(abs(rng), player);
        if(timerInsertCoin >= 1)
            insertCoin(abs(rng) / 1234, player);
        if(timerInsertPlanet >= 10)
            insertPlanet(abs(rng) / 100, player);
        if(timerInsertWarZone >= 20)
            insertWarZone(abs(rng) / 100000, player);
    }

    // Collision detection & CheckPastYet
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i, player, dt) || checkPastYet(*i, player))
            entityList.erase(i);
        else
            i++;
    }

    // Update Player
    if(!player.getIsExplode()){
        // Keyboard Input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.moveRight();

        // Guarentee Ship moves up
        player.setVelocity(player.getVelocity().x, player.getVelocity().y - 1.25 * player.getSpeed());
    }
    player.update(dt);

    // Update Entities
    for(auto const& i: entityList)
        i->update(dt);

    // Update Text
    updateText(player);

    // Update View
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, player.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt, player) != 0){
        game->push_state(new EventState(game, checkBadEvent(dt, player)));
        reset(player);
    }
}

void PlayState::draw(){
    draw(game->player1);
}

void PlayState::draw(Player& player){
    // Draw Background
    game->window.clear(sf::Color(8,29,49));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityList)
        i->draw(game->window);

    // Draw Player
    player.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);

    // Fade
    if(fadeTimer <= 3)
        fadeIn();
    if(timerCrash >= 2 || timerOffCourse >= 4)
        fadeOut();
}

void PlayState::updateText(Player& player){
    // Gold
    std::string goldString = "GOLD\t\t" + std::to_string(player.getGold());
    gameText[0].setString(goldString);

    // Crew
    std::string crewString = "CREW\t\t" + std::to_string(player.getCrew());
    gameText[1].setString(crewString);

    // Dist
    int dist = abs(player.getPosition().y);
    dist -= dist % 100;
    std::string distString = "DISTANCE\t" + std::to_string(dist) + " miles";
    gameText[2].setString(distString);

    // Velocity
    float vel = - player.getVelocity().y * 1000;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << vel;
    std::string velocityString = "VELOCITY\t" + stream.str() + " mph";
    gameText[3].setString(velocityString);

    // Move strings
    for(int i = 0; i < 4; i++)
        gameText[i].move(0, player.getVelocity().y);
}

void PlayState::reset(Player& player){
    for(auto key: entityList)
        delete key;
    entityList.clear();
    fadeTimer = 0;
    timerInsertAsteroid = 0;
    timerInsertCoin = 0;
    timerInsertPlanet = 0;
    timerCrash = 0;
    timerOffCourse = 0;
    timerInWarZone = 0;
    player.reset();
    player.setPosition(VIEW_WIDTH / 2, player.getPosition().y);
}

bool PlayState::collide(Entity* obj, Player& player, float dt){
    if(obj->name() == "Coin")
        return collide(dynamic_cast<Coin*>(obj), player);
    else if(obj->name() == "WarZone")
        return collide(dynamic_cast<WarZone*>(obj), player, dt);
    else
        return collide(dynamic_cast<Obstacle*>(obj), player);
}

bool PlayState::collide(Obstacle* obj, Player& player){
    if(PixelPerfectTest(player.getLeftWing(), obj->getBody()))
        player.hitLeft();
    else if(PixelPerfectTest(player.getRightWing(), obj->getBody()))
        player.hitRight();
    if(PixelPerfectTest(player.getBody(), obj->getBody()) && !player.getIsExplode()){
        sound.play();
        player.explode();
    }
    return 0;
}

bool PlayState::collide(Coin* obj, Player& player){
    if(PixelPerfectTest(player.getLeftWing(), obj->getBody())){
        player.gainGold();
        return 1;
    }
    else if(PixelPerfectTest(player.getRightWing(), obj->getBody())){
        player.gainGold();
        return 1;
    }
    else if(PixelPerfectTest(player.getBody(), obj->getBody())){
        player.gainGold();
        return 1;
    }
    return 0;
}

bool PlayState::collide(WarZone* obj, Player& player, float dt){
    if(PixelPerfectTest(player.getLeftWing(), obj->getBody()) && PixelPerfectTest(player.getRightWing(), obj->getBody())){
        player.healLeft();
        player.healRight();
        timerInWarZone += dt;
    }
    else
        timerInWarZone = 0;
    return 0;
}

bool PlayState::checkPastYet(Entity* obj, Player& player){
    float objHalfSize = obj->getGlobalBounds().height / 2;
    float dy = obj->getPosition().y - player.getPosition().y;
    if( dy - objHalfSize >= VIEW_HEIGHT / 6)
        return true;
    else
        return false;
}

int PlayState::checkBadEvent(float dt, Player& player){
    // Check if staying in WarZone too long
    if(timerInWarZone > 2){
        player.explode();
        if(!player.getIsExplode())
            sound.play();
    }

    // Check if exploded
    if(player.getIsExplode()){
        timerCrash += dt;
        if(timerCrash >= 3){
            if(player.getCrew() > 3)
                return 1;
            else
                return 2;
        }
    }

    // Check if veered off course
    if(player.getPosition().x < 0 || player.getPosition().x > VIEW_WIDTH){
        if(player.getPosition().x < 0)
            player.hitLeft();
        else
            player.hitRight();

        timerOffCourse += dt;
        if(timerOffCourse >= 5)
            return 3;
    }
    else
        timerOffCourse = 0;

    return 0;
}

void PlayState::insertAsteroid(int rngVal, Player& player){
    entityList.push_back(new Asteroid(&asteroidTexture, sf::Vector2u(4,4),
        /*Position*/                sf::Vector2f(rngVal % 2048, player.getPosition().y - 2 * VIEW_HEIGHT),
        /*Select Image*/            rngVal % 4, (rng / 100000) % 4,
        /*Rotation*/                0.3,
        /*Scale*/                   1 ));
    timerInsertAsteroid = 0;
}

void PlayState::insertCoin(int rngVal, Player& player){
    entityList.push_back(new Coin(&coinTexture, sf::Vector2u(10,1),
        /*Position*/            sf::Vector2f(rngVal % 2048, player.getPosition().y - 2 * VIEW_HEIGHT)));
    timerInsertCoin = 0;
}

void PlayState::insertPlanet(int rngVal, Player& player){
    float side;
    if(rngVal % 2)
        side = -1/2 * VIEW_WIDTH;
    else
        side = 3/2 * VIEW_WIDTH;
    entityList.push_back(new Planet(&planetTexture, sf::Vector2u(4,1),
        /*Position*/                sf::Vector2f(side, player.getPosition().y - VIEW_HEIGHT * 2),
        /*Select Image*/            rng % 4, 0,
        /*Rotation*/                0,
        /*Scale*/                   3 ));
    timerInsertPlanet = 0;
}

void PlayState::insertWarZone(int rngVal, Player& player){
    float side;
    if(rngVal % 2)
        side = -1/2 * VIEW_WIDTH;
    else
        side = 3/2 * VIEW_WIDTH;
    entityList.push_back(new WarZone(&warZoneTexture,
        /*Position*/                sf::Vector2f(side, player.getPosition().y - VIEW_HEIGHT * 6),
        /*Scale*/                   3 ));
    timerInsertWarZone = 0;
}
