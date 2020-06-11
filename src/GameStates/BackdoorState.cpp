#include "GameState.h"

using namespace Resource;

BackdoorState::BackdoorState(Game* game): PlayState(game, game->defaultPlayer), MenuState(game, 8){
	//Sound
	soundList.stopAllSounds();

    // Title
    title.setPosition(VIEW_WIDTH * 2.0/5.0, VIEW_HEIGHT/20.0);
    title.setString("ENDLESS\n    VOID Backdoor");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[4]);
        buttons[i].setPosition(VIEW_WIDTH/20.0, player.getPosition().y - VIEW_HEIGHT/2.0 + i * 40 * VIEW_RATIO);
        buttons[i].setCharacterSize(40 * VIEW_RATIO);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[0].setString("Key 1: Insert Asteroid");
    buttons[1].setString("Key 2: Insert Planet");
    buttons[2].setString("Key 3: Insert Coin");
    buttons[3].setString("Key 4: Insert WarZone");
    buttons[4].setString("Key 5: Add Crew");
    buttons[5].setString("Key 6: Lose Crew");
    buttons[6].setString("Key 7: Add Gold");
    buttons[7].setString("Key 8: Lose Gold");
}

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
            else if(event.key.code == sf::Keyboard::Num5)
                player.gainCrew();
            else if(event.key.code == sf::Keyboard::Num6)
                player.loseCrew();
            else if(event.key.code == sf::Keyboard::Num7)
                player.gainGold();
            else if(event.key.code == sf::Keyboard::Num8)
                player.loseGold();
            break;
        case sf::Event::MouseMoved:
            for(auto& i : buttons){
                if(isTextClicked(i))
                    i.setFillColor(sf::Color::Red);
                else
                    i.setFillColor(sf::Color::White);
            }
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
    if(!player.getIsExplode() && !player.getIsSucked()){
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
    updateText(dt);

    // Update Buttons
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if (isTextClicked(buttons[0]))
            insertAsteroid(rng, 600);
        else if(isTextClicked(buttons[1]))
            insertPlanet(rng, 600);
        else if(isTextClicked(buttons[2]))
            insertCoin(rng, 600);
        else if(isTextClicked(buttons[3]))
            insertWarZone(rng, 600 * 6);
        else if(isTextClicked(buttons[4]))
            player.gainCrew();
        else if(isTextClicked(buttons[5]))
            player.loseCrew();
        else if(isTextClicked(buttons[6]))
            player.gainGold();
        else if(isTextClicked(buttons[7]))
            player.loseGold();
        clickTimer = 0;
    }
    for(auto& i: buttons)
        i.move(0, player.getVelocity().y * dt);

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

    for(auto key : buttons)
        game->window.draw(key);
}
