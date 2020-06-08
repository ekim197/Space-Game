#include "GameState.h"

using namespace Resource;

BackdoorState::BackdoorState(Game* game): PlayState(game, game->defaultPlayer){}

void BackdoorState::handle_input(){
    sf::Event event;
    while (this->game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;
        // Pause game
        case sf::Event::LostFocus:
            game->push_state(new PauseState(game, game->current_state()));
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new PauseState(game, game->current_state()));
            else if(event.key.code == sf::Keyboard::Num1)
                insertAsteroid(rng, 600);
            else if(event.key.code == sf::Keyboard::Num2)
                insertPlanet(rng, 600);
            else if(event.key.code == sf::Keyboard::Num3)
                insertCoin(rng, 600);
            else if(event.key.code == sf::Keyboard::Num4)
                insertWarZone(rng, 600*6);
            break;
        default:
            break;
        }
    }
}

void BackdoorState::update(const float dt){
    // Three second delay before things start spawning in
    timeIncrement(dt);

    // Collision detection & CheckPastYet
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i,  dt) || checkPastYet(*i))
            i = entityList.erase(i);
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
        game->push_state(new EventState(game, dynamic_cast<PlayState*>(game->current_state()), checkBadEvent(dt)));
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
