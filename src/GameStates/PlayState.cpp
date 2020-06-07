#include "GameState.h"
#include <iostream>

using namespace Collision;

PlayState::PlayState(Game* game) : timerInsertAsteroid(0), timerInsertCoin(0), timerInsertPlanet(0), timerCrash(0){
    // Push Game
    this->game = game;

    // Reset Player1
    game->player1.setPosition(VIEW_WIDTH/2, game->player1.getPosition().y);
    game->player1.reset();

    // Text Stuff
    sf::Text tempText;
    tempText.setFont(game->font[0]);
    tempText.setCharacterSize(30);
    tempText.setFillColor(sf::Color::White);

    for(int i = 0; i < 3; i++){
        gameText.push_back(tempText);
        gameText[i].setPosition(100 , game->player1.getPosition().y - VIEW_HEIGHT * 8/10 + i * 50);
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
                pause_game();
            break;
        default:
            break;
        }
    }
}

void PlayState::update(const float dt){
    // Three second delay before things start spawning in
    timer += dt;
    fadeTimer += dt;

    if(timer > 3){
        // Time
        timerInsertAsteroid += dt;
        timerInsertCoin += dt;
        timerInsertPlanet += dt;

        // Insert Entities
        if(timerInsertAsteroid >= 0.5)
            insertAsteroid(abs(game->rng));
        if(timerInsertCoin >= 1)
            insertCoin(abs(game->rng) / 1234);
        if(timerInsertPlanet >= 10)
            insertPlanet(abs(game->rng) / 100);
    }

    // Collision detection & CheckPastYet
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i) || checkPastYet(*i))
            entityList.erase(i);
        else
            i++;
    }

    // Update Classes
    game->player1.update(dt);
    for(auto const& i: entityList)
        i->update(dt);

    // Update Text
    std::string goldString = "GOLD: " + std::to_string(game->player1.getGold());
    std::string crewString = "CREW: " + std::to_string(game->player1.getCrew());
    int dist = abs(game->player1.getPosition().y);
    dist -= dist % 100;
    std::string distString = "DIST: " + std::to_string(dist) + " km";

    gameText[0].setString(goldString);
    gameText[1].setString(crewString);
    gameText[2].setString(distString);

    for(int i = 0; i < 3; i++)
        gameText[i].move(0, game->player1.getVelocity().y);

    // Update View
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, game->player1.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt) != 0){
        game->push_state(new EventState(game, checkBadEvent(dt)));
        reset();
    }
}

void PlayState::draw(){
    // Draw Background
    game->window.clear(sf::Color(8,29,49));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityList)
        i->draw(game->window);

    // Draw Player
    game->player1.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);

    // Fade
    if(fadeTimer <= 3)
        fadeIn();
    if(timerCrash >= 2 || timerOffCourse >= 4)
        fadeOut();
}

void PlayState::reset(){
    for(auto key: entityList)
        delete key;
    entityList.clear();
    fadeTimer = 0;
    timerInsertAsteroid = 0;
    timerInsertCoin = 0;
    timerInsertPlanet = 0;
    timerCrash = 0;
    timerOffCourse = 0;
    game->player1.reset();
    game->player1.setPosition(VIEW_WIDTH / 2, game->player1.getPosition().y);
}

bool PlayState::collide(Entity* obj){
    sf::Vector2f objHalfSize(obj->getGlobalBounds().width / 2, obj->getGlobalBounds().height / 2);
    sf::Vector2f playerHalfSize(game->player1.getGlobalBounds().width / 2, game->player1.getGlobalBounds().height / 2);
    float dy = abs(obj->getPosition().y - game->player1.getPosition().y);
    float dx = abs(obj->getPosition().x - game->player1.getPosition().x);

    if(dy > objHalfSize.y + playerHalfSize.y || dx > objHalfSize.x + playerHalfSize.x){
        return false;
    }
    else{
        if(obj->name() == "Coin")
            return collide(dynamic_cast<Coin*>(obj));
        else
            return collide(dynamic_cast<Obstacle*>(obj));
    }
}

bool PlayState::collide(Obstacle* obj){
    // Main body
    if(PixelPerfectTest(game->player1.getBody(), obj->getBody()) && !game->player1.getIsExplode()){
        game->sound.play();
        game->player1.explode();
    }
    // Right Wing Collision detection
    if(PixelPerfectTest(game->player1.getRightWing(), obj->getBody())){
        game->player1.hitRight();
    }
    // Left Wing Collision detection
    if(PixelPerfectTest(game->player1.getLeftWing(), obj->getBody())){
        game->player1.hitLeft();
    }
    return 0;
}

bool PlayState::collide(Coin* obj){
    if(PixelPerfectTest(game->player1.getBody(), obj->getBody())){
        game->player1.gainGold();
        return 1;
    }
    else if(PixelPerfectTest(game->player1.getRightWing(), obj->getBody())){
        game->player1.gainGold();
        return 1;
    }
    else if(PixelPerfectTest(game->player1.getLeftWing(), obj->getBody())){
        game->player1.gainGold();
        return 1;
    }
    return 0;
}

bool PlayState::checkPastYet(Entity* obj){
    float objHalfSize = obj->getGlobalBounds().height / 2;
    float dy = obj->getPosition().y - game->player1.getPosition().y;
    if( dy - objHalfSize >= VIEW_HEIGHT / 6)
        return true;
    else
        return false;
}

int PlayState::checkBadEvent(float dt){
    // Check if exploded
    if(game->player1.getIsExplode()){
        timerCrash += dt;
        if(timerCrash >= 3){
            if(game->player1.getCrew() > 3)
                return 1;
            else
                return 2;
        }
    }

    // Check if veered off course
    if(game->player1.getPosition().x < 0 || game->player1.getPosition().x > VIEW_WIDTH){
        timerOffCourse += dt;
        if(timerOffCourse >= 5)
            return 3;
    }
    else
        timerOffCourse = 0;

    return 0;
}

void PlayState::insertAsteroid(int rng){
    entityList.push_back(new Asteroid( &game->asteroidTexture, sf::Vector2u(4,4),
        /*Position*/                sf::Vector2f(rng % 2048, game->player1.getPosition().y - 2 * VIEW_HEIGHT),
        /*Select Image*/            rng % 4, (rng / 100000) % 4,
        /*Rotation*/                0.3,
        /*Scale*/                   1 ));
    timerInsertAsteroid = 0;
}

void PlayState::insertCoin(int rng){
    entityList.push_back(new Coin( &game->coinTexture, sf::Vector2u(10,1),
        /*Position*/            sf::Vector2f(rng % 2048, game->player1.getPosition().y - 2 * VIEW_HEIGHT)));
    timerInsertCoin = 0;
}

void PlayState::insertPlanet(int rng){
    float side;
    if(rng%2)
        side = -1/2 * VIEW_WIDTH;
    else
        side = 3/2 * VIEW_WIDTH;
    entityList.push_back(new Planet( &game->planetTexture, sf::Vector2u(4,1),
        /*Position*/                sf::Vector2f(side, game->player1.getPosition().y - VIEW_HEIGHT * 2),
        /*Select Image*/            rng % 4, 0,
        /*Rotation*/                0,
        /*Scale*/                   3 ));
    timerInsertPlanet = 0;
}

void PlayState::pause_game(){
    game->push_state(new PauseState(game));
}

