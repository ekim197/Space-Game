#include <SFML\Graphics.hpp>
#include "Gamestate.h"

using namespace Resource;

EventState::EventState(Game* game, PlayState* prev, int type): prevState(prev), eventType(type){
    // Push Game
    this->game = game;

    // Background
    background.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT * 2/3));

    // Text
    textInfo.setFont(font[4]);
    textInfo.setPosition(300, 825);
    textInfo.setCharacterSize(50); // in pixels, not points!
    textInfo.setFillColor(sf::Color::White);

    textInfo2.setFont(font[4]);
    textInfo2.setPosition(400, 875);
    textInfo2.setCharacterSize(50); // in pixels, not points!
    textInfo2.setFillColor(sf::Color::White);

    sf::Text textOption1; //text for choices button
    textOption1.setFont(font[3]);
    textOption1.setPosition(400, 1000);
    textOption1.setCharacterSize(35); // in pixels, not points!
    textOption1.setFillColor(sf::Color::White);

    for (int i = 0; i < 2; i++){
        choiceButtons.push_back(textOption1);
        choiceButtons[i].setPosition(textOption1.getPosition().x, textOption1.getPosition().y + i * 50);
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
        choiceButtons[1].setString("Option 2: Pay 3 gold to use the module (guarantee to get back)");
    }
	else if (eventType == planet) {
		background.setTexture(&backgroundTexture[12]);

		textInfo.setString("You are being sucked into the planet! Blow into the mic to get sucked back out into space!");
		textInfo2.setString("Press the start button to begin blowing");

		choiceButtons[0].setString("Start");

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
				if (rng % 100 > 60) {
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
				if (rng % 100 > 50){
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
				if (rng % 100 > 50) {
					if (prevState->player.getGold() < 3) {
						game->push_state(new OutcomeState(game, prevState, OutcomeState::veerFail));
					}
					else {
						game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess));
					}
				}
				else {
					prevState->player.loseGold(3);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess2));
				}
			}
			else if (isTextClicked(choiceButtons[1])) {
			    soundList.playSound(RESOURCE_PATH + "Audio/Bells_Cut.wav");
				if (prevState->player.getGold() < 3) {
					if (rng % 100 > 50) {
						game->push_state(new OutcomeState(game, prevState, OutcomeState::veerFail));
					}
					else {
						game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess));
					}
				}
				else {
					prevState->player.loseGold(3);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::veerSuccess2));
				}
			}
		}
		else if (eventType == planet) {
			if (isTextClicked(choiceButtons[0])) {
				soundList.stopAllSounds();
				soundList.playSound(RESOURCE_PATH + "Audio/ButtonClick.wav", 400);
				int largestAmplitude = soundList.RecordSoundAndGetAmplitude(3000);
				std::cout << largestAmplitude;
				if (largestAmplitude < 5000) {
					game->push_state(new OutcomeState(game, prevState, OutcomeState::suckFail));
				}
				else {
					game->push_state(new OutcomeState(game, prevState, OutcomeState::suckSuccess));
				}
			}
		}
        clickTimer = 0;
    }
}

