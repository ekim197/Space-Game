#include "GameState.h"

using namespace Resource;

TutorialState::TutorialState(Game* game): PlayState(game, game->defaultPlayer){
    for(auto& key: gameText)
        key.setFillColor(sf::Color::Red);

    // Instruction Text
    instruction.setFont(font[0]);
    instruction.setCharacterSize(30);
    instruction.setFillColor(sf::Color::Red);
    instruction.setPosition(100, player.getPosition().y - 100);

    // Instruction Properties
    for(size_t i = 0; i < 5; i++){
        isInstrPass[i] = false;
        instrTimer[i] = 0;
    }
}

void TutorialState::update(const float dt){
    // Always increment these Time Variables
    timeIncrement(dt);

    // Instruction 1
    if(!isInstrPass[0]){
        instruction.setString("Welcome to the tutorial\n Begin by using the A and D key\n to move left and right");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            instrTimer[0] += dt;
        if(instrTimer[0] > 3)
            isInstrPass[0] = true;
    }
    // Instruction 2
    else if(!isInstrPass[1]){
        instruction.setString("Some Obstacles will spawn\n  If your main body hits them\n  you instantly crash\n\nTry to dodge them for 10 seconds");
        timerInsertAsteroid += dt;
        timerInsertPlanet += dt;
        instrTimer[1] += dt;

        if(instrTimer[1] > 10)
            isInstrPass[1] = true;
    }
    // Instruction 2
    else if(!isInstrPass[2]){
        instruction.setString("Well Done!\nNow coins will spawn.\n\nCollect 5 coins");
        timerInsertCoin += dt;

        if(player.getGold() >= 5)
            instrTimer[2] += dt;

        if(instrTimer[2] > 1){
            isInstrPass[2] = true;
            insertWarZone(abs(rng) / 100000, VIEW_HEIGHT * 6);
        }
    }
    // Instruction 3
    else if(!isInstrPass[3]){
        instruction.setString("Great!\nYour Wings are hit now!\nGet in the Orange War Zone to heal\nBe careful, stay too long in there\nand you explode!");

        timerInsertWarZone += dt;

        if(player.getNumLeftHit() < 200 && player.getNumRightHit() < 200 && timerInsertWarZone < 1){
            player.hitLeft();
            player.hitRight();
        }


        if(player.getNumLeftHit() == 0 && player.getNumRightHit() == 0)
            instrTimer[3] += dt;

        if(instrTimer[3] > 1)
            isInstrPass[3] = true;
    }
    else if(!isInstrPass[4]){
        instruction.setString("Nice!\n If you crash, you will get into an event\n");

    }

    // Insert Entities
    if(timerInsertAsteroid >= 1)
        insertAsteroid(abs(rng), VIEW_HEIGHT * 2);
    if(timerInsertCoin >= 1)
        insertCoin(abs(rng) / 1234, VIEW_HEIGHT * 2);
    if(timerInsertPlanet >= 5)
        insertPlanet(abs(rng) / 100, VIEW_HEIGHT * 2);
    if(timerInsertWarZone >= 15){
        insertWarZone(abs(rng) / 100000, VIEW_HEIGHT * 6);
        timerInsertWarZone = 2;
    }

    //Collision detection
    auto i = entityList.begin();
    while(i != entityList.end()){
        if(collide(*i, dt) || checkPastYet(*i))
            i = entityList.erase(i);
        else
            i++;
    }

    // Update Player
    if(!player.getIsExplode()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player.moveLeft();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.moveRight();

        // Guarantee Ship moves up
        player.setVelocity(player.getVelocity().x, player.getVelocity().y - .75 * player.getSpeed());
    }
    player.update(dt);

    // Update Entities
    for(auto const& i: entityList)
        i->update(dt);

    // Update Text Movement
    updateText(dt);
    instruction.move(0, player.getVelocity().y * dt);
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, player.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt) != 0){
        game->push_state(new EventState(game, dynamic_cast<PlayState*>(game->current_state()), checkBadEvent(dt)));
        reset();
    }
}

void TutorialState::draw(){
    // Draw Background
    game->window.clear(sf::Color(230,230,230));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityList)
        i->draw(game->window);

    // Draw Player
    player.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);

    game->window.draw(instruction);

    // Fade
    if(fadeTimer <= 3)
        fadeIn();
    if(timerCrash >= 2 || timerOffCourse >= 4)
        fadeOut();
}
