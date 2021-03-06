#include "GameState.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace Collision;
using namespace Resource;

PlayState::PlayState(Game* game, Player& playerObj)
    : timerInsertAsteroid(0), timerInsertCoin(0), timerInsertPlanet(0), timerCrash(0), timerSuck(0),
      timerOffCourse(0), timerInWarZone(0), timerAddAsteroid(0), asteroidPerTime(1), player(playerObj){
    //Sound Stuff
	soundList.stopAllSounds();
	soundList.playSound(RESOURCE_PATH + "Audio/PlayState.ogg");

    // Push Game
    this->game = game;

    // Reset Player1
    player.setPosition(VIEW_WIDTH/2, player.getPosition().y);
    player.reset();

    // Text Stuff
    sf::Text tempText;
    tempText.setFont(font[0]);
    tempText.setCharacterSize(30 * VIEW_RATIO);
    tempText.setFillColor(sf::Color::White);

    for(auto i = 0; i < 4; i++){
        gameText.push_back(tempText);
        gameText[i].setPosition(VIEW_WIDTH * 3.0/4.0 , player.getPosition().y - VIEW_HEIGHT * 4.0/5.0 + i * 50.0 * VIEW_RATIO);
    }
}

PlayState::~PlayState(){
    for(auto key: entityVector)
        delete key;
    entityVector.clear();
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
        case sf::Event::LostFocus:
            game->push_state(new PauseState(game, game->current_state()));
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new PauseState(game, game->current_state()));
            break;
        default:
            break;
        }
    }
}

void PlayState::update(const float dt){
    if (!soundList.getStatusOfMusic(RESOURCE_PATH + "Audio/PlayState.ogg")){
	soundList.stopAllSounds();
	soundList.playSound(RESOURCE_PATH + "Audio/PlayState.ogg");
    }


    // Three second delay before things start spawning in
    timeIncrement(dt);

    if(timer > 3){
        // Time
        timerInsertAsteroid += dt;
        timerInsertCoin += dt;
        timerInsertPlanet += dt;
        timerInsertWarZone += dt;
        timerAddAsteroid += dt;

        // Makes Game Harder
        if(timerAddAsteroid >= 20){
            asteroidPerTime++;
            timerAddAsteroid = 0;
        }

        // Insert Entities
        if(timerInsertAsteroid >= 0.5){
            for(int i = 0; i < asteroidPerTime; i++)
                insertAsteroid(abs(rng / (i + 1)), VIEW_HEIGHT * 2);
        }
        if(timerInsertCoin >= 1)
            insertCoin(abs(rng) / 1234, VIEW_HEIGHT * 2);
        if(timerInsertPlanet >= 10)
            insertPlanet(abs(rng) / 100, VIEW_HEIGHT * 2);
        if(timerInsertWarZone >= 20)
            insertWarZone(abs(rng) / 100000, VIEW_HEIGHT * 6);
    }

    // Collision detection & CheckPastYet
    try{
        auto i = entityVector.begin();
        while(i != entityVector.end()){
            if(collide(*i, dt) || checkPastYet(*i))
                i = entityVector.erase(i);
            else
                i++;
        }
    }
    catch(const std::string& error){
        std::cerr << "\n\n" << error << "\n\n";
        exit(2);
    }

    // Update Player
    if(!player.getIsExplode() && !player.getIsSucked()){
        // Keyboard Input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.moveRight();

        // Guarantee Ship moves up
        player.setVelocity(player.getVelocity().x, player.getVelocity().y - 1.25 * player.getSpeed());
    }
    player.update(dt);

    // Update Entities
    for(auto const& i: entityVector)
        i->update(dt);

    // Update Text
    updateText(dt);

    // Update View
    game->view.setCenter(sf::Vector2f(VIEW_WIDTH/2, player.getPosition().y - VIEW_HEIGHT/3));

    // Check if exploded
    if(checkBadEvent(dt) != 0){
        game->push_state(new EventState(game, dynamic_cast<PlayState*>(game->current_state()), checkBadEvent(dt)));
        reset();
    }

    // Check if Crew Dead
    if(player.getCrew() <= 0)
        game->push_state(new EndState(game, dynamic_cast<PlayState*>(game->current_state())));
}

void PlayState::draw(){
    // Draw Background
    game->window.clear(sf::Color(8,29,49));
    game->window.setView(game->view);

    // Draw Entities
    for(auto const& i: entityVector)
        i->draw(game->window);

    // Draw Player
    player.draw(game->window);

    // Draw Text
    for(auto i : gameText)
        game->window.draw(i);

    // Fade
    if(fadeTimer <= 3)
        fadeIn();
    if(timerCrash >= 2 || timerOffCourse >= 2 || timerSuck >= 2)
        fadeOut();
}

void PlayState::updateText(const float dt){
    // Gold
    std::string goldString = "GOLD\t\t" + std::to_string(player.getGold());
    gameText[0].setString(goldString);

    // Crew
    std::string crewString = "CREW\t\t" + std::to_string(player.getCrew());
    gameText[1].setString(crewString);

    // Dist
    int dist = round(-player.getPosition().y);
    std::string distString = "DISTANCE\t" + std::to_string(dist) + " miles";
    gameText[2].setString(distString);

    // Velocity
    float vel = round(- player.getVelocity().y);
    std::stringstream sout;
    sout << std::fixed << std::setprecision(0) << vel;
    std::string velocityString = "VELOCITY\t" + sout.str() + " mph";
    gameText[3].setString(velocityString);

    // Move strings
    for(int i = 0; i < 4; i++)
        gameText[i].move(0, player.getVelocity().y * dt);
}

void PlayState::reset(){
    for(auto key: entityVector)
        delete key;
    entityVector.clear();
    fadeTimer = 0;
    timerInsertAsteroid = 0;
    timerInsertCoin = 0;
    timerInsertPlanet = 0;
    timerCrash = 0;
	timerSuck = 0;
    timerOffCourse = 0;
    timerInWarZone = 0;
    timerAddAsteroid = 0;
    asteroidPerTime = 1;
    player.reset();
    player.setPosition(VIEW_WIDTH / 2, player.getPosition().y);
}

bool PlayState::collide(Entity* obj, float dt){
    if(obj){
		if (obj->name() == "Coin")
			return collide(dynamic_cast<Coin*>(obj));
		else if (obj->name() == "WarZone")
			return collide(dynamic_cast<WarZone*>(obj), dt);
		else if (obj->name() == "Planet")
			return collide(dynamic_cast<Planet*>(obj));
        else
            return collide(dynamic_cast<Obstacle*>(obj));
    }
    return 0;
}

bool PlayState::collide(Obstacle* obj){
    if(obj){
        if(PixelPerfectTest(player.getLeftWing(), obj->getBody()))
            player.hitLeft();
        else if(PixelPerfectTest(player.getRightWing(), obj->getBody()))
            player.hitRight();
        if(PixelPerfectTest(player.getBody(), obj->getBody()) && !player.getIsExplode()){
            soundList.playSound(RESOURCE_PATH + "Audio/Ship_Explosion.wav", 10);
            player.explode();
        }
    }
    return 0;
}

bool PlayState::collide(Planet* obj) {
	if (obj) {
		if (PixelPerfectTest(player.getBody(), obj->getBody()) && !player.getIsSucked()) {
			soundList.playSound(RESOURCE_PATH + "Audio/Tornado.wav", 110);
			player.sucked();
		}
	}
	return 0;
}

bool PlayState::collide(Coin* obj){
    if(obj){
        if(PixelPerfectTest(player.getLeftWing(), obj->getBody())){
            soundList.playSound(RESOURCE_PATH + "Audio/Coin_Collect.wav", 15, 0.4);
            player.gainGold();
            return 1;
        }
        else if(PixelPerfectTest(player.getRightWing(), obj->getBody())){
            soundList.playSound(RESOURCE_PATH + "Audio/Coin_Collect.wav", 15, 0.4);
            player.gainGold();
            return 1;
        }
        else if(PixelPerfectTest(player.getBody(), obj->getBody())){
            soundList.playSound(RESOURCE_PATH + "Audio/Coin_Collect.wav", 15, 0.4);
            player.gainGold();
            return 1;
        }
    }
    return 0;
}

bool PlayState::collide(WarZone* obj, float dt){
    if(obj){
        if(PixelPerfectTest(player.getLeftWing(), obj->getBody()) && PixelPerfectTest(player.getRightWing(), obj->getBody())){
			if(!player.getIsInWarZone())
                soundList.playSoundConcurrently(RESOURCE_PATH + "Audio/WarZone2.wav", 10);
            player.healLeft();
            player.healRight();
            timerInWarZone += dt;
			player.warZone();
        }
		else{
			timerInWarZone = 0;
            player.unWarZone();
		}
    }
    return 0;
}

bool PlayState::checkPastYet(Entity* obj){
    if(obj){
        float objHalfSize = obj->getGlobalBounds().height / 2;
        float dy = obj->getPosition().y - player.getPosition().y;
        if( dy - objHalfSize >= VIEW_HEIGHT / 6)
            return true;
        else
            return false;
    }
    else
        return false;
}

int PlayState::checkBadEvent(float dt){
    // Check if staying in WarZone too long
    if (timerInWarZone > 2 && !player.getIsExplode()) {
		soundList.playSound(RESOURCE_PATH + "Audio/Ship_Explosion.wav", 10);
		player.explode();
	}

    // Check if exploded
    if(player.getIsExplode()){
        timerCrash += dt;
        if(timerCrash >= 3){
            if(timerInWarZone > 2){
                return 5;
            }
            else{
                if(player.getCrew() > 3)
                    return 1;
                else
                    return 2;
            }
        }
    }

    // Check if veered off course
    if(player.getPosition().x < 0 || player.getPosition().x > VIEW_WIDTH){
        if(player.getPosition().x < 0)
            player.hitLeft();
        else
            player.hitRight();

        timerOffCourse += dt;
        if(timerOffCourse >= 3)
            return 3;
    }
    else
        timerOffCourse = 0;

    // Check if collision with planet
	if (player.getIsSucked()) {
		timerSuck += dt;
		if (timerSuck >= 3) {
			return 4;
		}
	}

    return 0;
}

void PlayState::insertAsteroid(int rngVal, float distY){
    entityVector.push_back(new Asteroid(&asteroidTexture, sf::Vector2u(4,4),
        /*Position*/                sf::Vector2f(rngVal % 2048, player.getPosition().y - distY),
        /*Select Image*/            rngVal % 4, (rng / 10000) % 4,
        /*Rotation*/                0.3,
        /*Scale*/                   1 ));
    timerInsertAsteroid = 0;
}

void PlayState::insertCoin(int rngVal, float distY){
    entityVector.push_back(new Coin(&coinTexture, sf::Vector2u(10,1),
        /*Position*/            sf::Vector2f(rngVal % 2048, player.getPosition().y - distY)));
    timerInsertCoin = 0;
}

void PlayState::insertPlanet(int rngVal, float distY){
    float side;
    if(rngVal % 2)
        side = -VIEW_WIDTH/20.0;
    else
        side = VIEW_WIDTH * 21.0/20.0;
    entityVector.push_back(new Planet(&planetTexture, sf::Vector2u(4,1),
        /*Position*/                sf::Vector2f(side, player.getPosition().y - distY),
        /*Select Image*/            rng % 4, 0,
        /*Rotation*/                0,
        /*Scale*/                   3 ));
    timerInsertPlanet = 0;
}

void PlayState::insertWarZone(int rngVal, float distY){
    float side;
    if(rngVal % 2)
        side = 0.0;
    else
        side = VIEW_WIDTH;
    entityVector.push_back(new WarZone(&warZoneTexture,
        /*Position*/                sf::Vector2f(side, player.getPosition().y - distY),
        /*Scale*/                   3 ));
    timerInsertWarZone = 0;
}

