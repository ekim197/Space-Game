#include "GameState.h"

using namespace Resource;

BackdoorState::BackdoorState(Game* game): PlayState(game, game->defaultPlayer){}

void BackdoorState::update(const float dt){
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
            insertAsteroid(abs(rng));
        if(timerInsertCoin >= 1)
            insertCoin(abs(rng) / 1234);
        if(timerInsertPlanet >= 10)
            insertPlanet(abs(rng) / 100);
        if(timerInsertWarZone >= 20)
            insertWarZone(abs(rng) / 100000);
    }

    // Collision detection & CheckPastYet
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i,  dt) || checkPastYet(*i))
            entityList.erase(i);
        else
            i++;
    }

    // Update Player
    if(!player.getIsExplode()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.moveDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.moveRight();
    }
    player.update(dt);

    // Update Entities
    for(auto const& i: entityList)
        i->update(dt);

    // Update Text
    updateText();
    // Update View
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, player.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt) != 0){
        game->push_state(new EventState(game, checkBadEvent(dt)));
        reset();
    }
}

void BackdoorState::draw(){
    // Draw Background
    game->window.clear(sf::Color(30,30,30));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityList)
        i->draw(game->window);

    // Draw Player
    player.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);
}
