#include <SFML\Graphics.hpp>
#include "Gamestate.h"
#include <iostream>


using namespace Resource;

EventState::EventState(Game* game, PlayState* prev, int type): prevState(prev), eventType(type){
    // Push Game
    this->game = game;

    // Music
    music[0].stop();
    music[1].play();

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

        choiceButtons[0].setString("");
        choiceButtons[1].setString("");
    }
    else if(eventType == veer){
        background.setTexture(&backgroundTexture[5]);

        textInfo.setString("Your ship has veered off course. You can use the");
        textInfo2.setString("findYourWayBack module by EngiAtom(EA) ");

        choiceButtons[0].setString("Option 1: Try to figure it out yourself(What's the worst that could happen)");
        choiceButtons[1].setString("Option 2: Pay 3 gold to use the module (guarantee to get back)");
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
    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt != 0){
		if (eventType == asteroid) {
			if (isTextClicked(choiceButtons[0])) {
				prevState->player.loseCrew();
				game->push_state(new OutcomeState(game, prevState, OutcomeState::astSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
				if (rng % 100 > 60) {
					prevState->player.loseCrew(3);
					game->push_state(new OutcomeState(game, prevState, OutcomeState::astFail));
				}
				game->push_state(new OutcomeState(game, prevState, OutcomeState::astSuccess2));
			}
		}
		else if (eventType == lastMember) {
			int chance = rng % 100;
			if (isTextClicked(choiceButtons[0])) {
				if (rng % 100 > 50) game->push_state(new OutcomeState(game, prevState, OutcomeState::lastFail));
				else game->push_state(new OutcomeState(game, prevState, OutcomeState::lastSuccess));
			}
			else if (isTextClicked(choiceButtons[1])) {
				if (rng % 100 > 50) game->push_state(new OutcomeState(game, prevState, OutcomeState::lastFail));
				else game->push_state(new OutcomeState(game, prevState, OutcomeState::lastSuccess));
			}
		}
		else if (eventType == veer) {
			if (isTextClicked(choiceButtons[0])) {
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
		//game->pop_state();
    }
}

bool EventState::isTextClicked(sf::Text text){
    float x = text.getPosition().x;
    float y = text.getPosition().y;
    float width = text.getGlobalBounds().width;
    float height = text.getGlobalBounds().height;
    sf::IntRect rect(x, y, width, height);
    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    //Otherwise, don't do anything
    return false;
}
