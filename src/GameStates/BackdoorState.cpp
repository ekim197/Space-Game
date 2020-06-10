#include "GameState.h"

using namespace Resource;

BackdoorState::BackdoorState(Game* game): PlayState(game, game->defaultPlayer), MenuState(game, 4){
	//Sound
	soundList.stopAllSounds();

    // Title
    title.setPosition(800,100);
    title.setString("ENDLESS\n    VOID Backdoor");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[4]);
        buttons[i].setPosition(100, player.getPosition().y - (550 + i * 80));
        buttons[i].setCharacterSize(75);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[0].setString("Insert Asteroid");
    buttons[1].setString("Insert Planet");
    buttons[2].setString("Insert Coin");
    buttons[3].setString("Insert WarZone");
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
    updateText(dt);

    // Update Buttons
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if (isTextClicked(buttons[0]))
            insertAsteroid(rng, 600);
        else if(isTextClicked(buttons[1]))
            insertPlanet(rng, 600);
        else if (isTextClicked(buttons[2]))
            insertCoin(rng, 600);
        else if (isTextClicked(buttons[3]))
            insertWarZone(rng, 600 * 6);
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

bool BackdoorState::isTextClicked(sf::Text text){
    sf::IntRect rect(text.getPosition().x, text.getPosition().y - (game->view.getCenter().y - VIEW_HEIGHT/2), text.getGlobalBounds().width, text.getGlobalBounds().height + 20);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}
