#include "GameState.h"

using namespace Resource;

BackdoorState::BackdoorState(Game* game){
    // Push Game
    this->game = game;

    // Reset Player1
    game->testPlayer.setPosition(VIEW_WIDTH/2, game->player1.getPosition().y);
    game->testPlayer.reset();

    // Text Stuff
    sf::Text tempText;
    tempText.setFont(font[0]);
    tempText.setCharacterSize(30);
    tempText.setFillColor(sf::Color::White);

    for(auto i = 0; i < 4; i++){
        gameText.push_back(tempText);
        gameText[i].setPosition(VIEW_WIDTH - 500 , game->player1.getPosition().y - VIEW_HEIGHT * 8/10 + i * 50);
    }
}

void BackdoorState::update(const float dt){
    update(dt, game->testPlayer);
}

void BackdoorState::update(const float dt, Player& player){
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
            insertAsteroid(abs(rng));
        if(timerInsertCoin >= 1)
            insertCoin(abs(rng) / 1234);
        if(timerInsertPlanet >= 10)
            insertPlanet(abs(rng) / 100);
    }

    // Collision detection & CheckPastYet
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i, player, dt) || checkPastYet(*i, player))
            entityList.erase(i);
        else
            i++;
    }

    // Update Classes
    player.update(dt);
    for(auto const& i: entityList)
        i->update(dt);

    // Update Text
    std::string goldString = "GOLD\t\t" + std::to_string(player.getGold());
    std::string crewString = "CREW\t\t" + std::to_string(player.getCrew());
    int dist = abs(player.getPosition().y);
    dist -= dist % 100;
    std::string distString = "DISTANCE\t" + std::to_string(dist) + " miles";
    std::string velocityString = "VELOCITY\t" + std::to_string(abs(player.getVelocity().y * 1000)) + " mph";

    gameText[0].setString(goldString);
    gameText[1].setString(crewString);
    gameText[2].setString(distString);
    gameText[3].setString(velocityString);

    for(int i = 0; i < 4; i++)
        gameText[i].move(0, player.getVelocity().y);

    // Update View
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, player.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt, player) != 0){
        game->push_state(new EventState(game, checkBadEvent(dt, player)));
        reset(player);
    }
}

void BackdoorState::draw(){
    // Draw Background
    game->window.clear(sf::Color(0,0,0));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityList)
        i->draw(game->window);

    // Draw Player
    game->testPlayer.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);
}
