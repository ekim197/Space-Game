#include <SFML\Graphics.hpp>
#include "Gamestate.h"

using namespace Resource;

EventState::EventState(Game* game, PlayState* prev, int type): prevState(prev), eventType(type){
    // Push Game
    this->game = game;

    // Background
    background.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT * 2.0/3.0));

    // Text
    textInfo.setFont(font[4]);
    textInfo.setPosition(VIEW_WIDTH * 3.0/20.0, VIEW_HEIGHT * 3.0/4.0);
    textInfo.setCharacterSize(50 * VIEW_RATIO); // in pixels, not points!
    textInfo.setFillColor(sf::Color::White);

    textInfo2.setFont(font[4]);
    textInfo2.setPosition(VIEW_WIDTH * 3.0/20.0, VIEW_HEIGHT * 4.0/5.0);
    textInfo2.setCharacterSize(50 * VIEW_RATIO); // in pixels, not points!
    textInfo2.setFillColor(sf::Color::White);

    for (int i = 0; i < 2; i++){
        choiceButtons.push_back(sf::Text());
        choiceButtons[i].setFont(font[3]);
        choiceButtons[i].setPosition(VIEW_WIDTH * 1.0/5.0, VIEW_HEIGHT * 9.0/10.0 + i * 35.0 * VIEW_RATIO);
        choiceButtons[i].setFillColor(sf::Color::White);
    }

    if(eventType == asteroid){
        background.setTexture(&backgroundTexture[3]);

        textInfo.setString("You crashed and the main hull is breached,");
        textInfo2.setString("someone is going to have to fix it, but its too risky...");

        choiceButtons[0].setString("Option 1: Sacrifice 1 person(guarantee to lose on passenger)");
        choiceButtons[1].setString("Option 2: Send out 3 people(60% chance they survive)");
    }
    else if(eventType == lastMember){
        background.setTexture(&backgroundTexture[4]);

        textInfo.setString("There isn't much of the crew left. There is no options left,");
        textInfo2.setString(" you must fix the ship, its a 50-50 chance you will live");

        choiceButtons[0].setString("Test your fate");
        choiceButtons[1].setString("Give up");
    }
    else if(eventType == veer){
        background.setTexture(&backgroundTexture[5]);

        textInfo.setString("Your ship has veered off course. You can use the");
        textInfo2.setString("findYourWayBack module by EngiAtom(EA) ");

        choiceButtons[0].setString("Option 1: Try to figure it out yourself(What's the worst that could happen)");
        choiceButtons[1].setString("Option 2: Pay 10 gold to use the module (guarantee to get back)");
    }
	else if (eventType == planet) {
		background.setTexture(&backgroundTexture[12]);

		textInfo.setString("You flew too close! The storms are sucking you in!");
		textInfo2.setString("Press Start and Blow into the mic to escape!");

		choiceButtons[0].setString("Start");
	}
    else if (eventType == warZone) {
		background.setTexture(&backgroundTexture[12]);

		textInfo.setString("Your ship was shot down!");
		textInfo2.setString("Its fight or flight!");

        choiceButtons[0].setString("Option 1: Fight(50% success)");
        choiceButtons[1].setString("Option 2: Flight(70% success)");
	}
}

void EventState::handle_input(){
    sf::Event event;

    while (game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
        //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new PauseState(game, game->current_state()));
            break;
        case sf::Event::LostFocus:
            game->push_state(new PauseState(game, game->current_state()));
            break;
        case sf::Event::MouseMoved:
            if (isTextClicked(choiceButtons[0]))
                choiceButtons[0].setFillColor(sf::Color::Red);
            else
                choiceButtons[0].setFillColor(sf::Color::White);
            if (isTextClicked(choiceButtons[1]))
                choiceButtons[1].setFillColor(sf::Color::Red);
            else
                choiceButtons[1].setFillColor(sf::Color::White);
        default:
            break;
        }
    }
}

void EventState::draw(){
    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    game->view.setCenter(view.getCenter());
    game->window.setView(view);

    game->window.clear();

    // Draws Buttons
    for (auto x : choiceButtons)
        game->window.draw(x);

    // Draw Backround and Text
    game->window.draw(background);
    game->window.draw(textInfo);
    game->window.draw(textInfo2);

    // Fade
    if(fadeTimer <= 3)
        fadeIn();
}

void EventState::update(const float dt){
	//Sound
	if (!soundList.getStatusOfMusic(RESOURCE_PATH + "Audio/EventStates.ogg")) {
		soundList.stopAllSounds();
		soundList.playSound(RESOURCE_PATH + "Audio/EventStates.ogg");
	}

    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
		if (eventType == asteroid) {
			if (isTextClicked(choiceButtons[0])) {
				soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				prevState->player.loseCrew();
				game->push_state(new OutcomeState(game, prevState, OutcomeState::astSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
				soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (rng % 10000 > 6000) {
					prevState->player.loseCrew(3);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::astFail));
				}
				else
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::astSuccess2));
			}
		}
		else if (eventType == lastMember) {
			if (isTextClicked(choiceButtons[0])) {
                soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (rng % 10000 > 5000){
                    prevState->player.loseCrew(prevState->player.getCrew());
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::lastFail));
				}
				else
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::lastSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
                soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				prevState->player.loseCrew(prevState->player.getCrew());
				game->push_state(new OutcomeState(game, prevState, OutcomeState::lastFail));
			}
		}
		else if (eventType == veer) {
			if (isTextClicked(choiceButtons[0])) {
			    soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (rng % 10000 > 5000) {
                    prevState->player.setCrew(0);
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::veerFail2));
				}
				else
					game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
			    soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (prevState->player.getGold() < 10) {
                    prevState->player.setCrew(0);
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::veerFail));
				}
				else {
					prevState->player.loseGold(10);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess2));
				}
			}
		}
		else if (eventType == planet) {
			if (isTextClicked(choiceButtons[0])) {
				soundList.stopAllSounds();
				soundList.playSound(RESOURCE_PATH + "Audio/ButtonClick.wav", 400);

				int minimumBlowAmplitude = 5000;
				int averageAmplitude = soundList.RecordSoundAndGetAmplitude(3000);

				if (averageAmplitude < minimumBlowAmplitude) {
					if(prevState->player.getCrew() > 4){
                        prevState->player.loseCrew(4);
                        game->push_state(new OutcomeState(game, prevState, OutcomeState::suckFail));
					}
                    else{
                        prevState->player.setCrew(0);
                        game->push_state(new OutcomeState(game, prevState, OutcomeState::suckFail2));
                    }
				}
				else {
					game->push_state(new OutcomeState(game, prevState, OutcomeState::suckSuccess));
				}
			}
		}
        else if (eventType == warZone) {
            if (isTextClicked(choiceButtons[0])) {
			    soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (rng % 10000 > 5000) {
                    prevState->player.loseCrew(2);
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::fightFail));
				}
				else
                    prevState->player.gainGold(10);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::fightSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
			    soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (rng % 10000 > 7000) {
                    prevState->player.loseCrew(3);
                    game->push_state(new OutcomeState(game, prevState, OutcomeState::flightSuccess));
				}
				else {
					game->push_state(new OutcomeState(game, prevState, OutcomeState::flightFail));
				}
			}
		}
        clickTimer = 0;
    }
}

