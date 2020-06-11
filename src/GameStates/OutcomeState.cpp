#include <SFML\Graphics.hpp>
#include "Gamestate.h"
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif
using namespace Resource;

OutcomeState::OutcomeState(Game* game, PlayState* prev, int type): prevState(prev), outcomeType(type) {
	// Push Game
	this->game = game;

    // Background
    background.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT * 2.0/3.0));

    // Text
    textInfo.setFont(font[4]);
    textInfo.setPosition(VIEW_WIDTH * 3.0/20.0, VIEW_HEIGHT * 7.0/10.0);
    textInfo.setCharacterSize(35 * VIEW_RATIO); // in pixels, not points!
    textInfo.setFillColor(sf::Color::White);

    textInfo2.setFont(font[4]);
    textInfo2.setPosition(VIEW_WIDTH * 3.0/20.0, VIEW_HEIGHT * 3.0/4.0);
    textInfo2.setCharacterSize(35 * VIEW_RATIO); // in pixels, not points!
    textInfo2.setFillColor(sf::Color::White);

    for (int i = 0; i < 2; i++){
        choiceButtons.push_back(sf::Text());
        choiceButtons[i].setFont(font[3]);
        choiceButtons[i].setPosition(VIEW_WIDTH * 1.0/5.0, VIEW_HEIGHT * 9.0/10.0 + i * 35.0 * VIEW_RATIO);
        choiceButtons[i].setFillColor(sf::Color::White);
    }

    // Assign Choice
	choiceButtons[0].setString("");
	choiceButtons[1].setString("Click here to continue");

	if (outcomeType == astSuccess) {
		background.setTexture(&backgroundTexture[4]);
		textInfo.setString("Your crew draw sticks, the person who drew the shortest stick\nlooked miserable, but there is no more going back.");
		textInfo2.setString("\nThe ship restarts, and we watched his lifeless body as we continue onward.\nWe can only hope that his sacrifice won't be in vain.");
	}
	else if (outcomeType == astSuccess2) {
		background.setTexture(&backgroundTexture[6]);
		textInfo.setString("They were able to fix the ship and all get back in one piece.");
		textInfo2.setString("Lets hope our luck continues.");
	}
	else if (outcomeType == astFail) {
		background.setTexture(&backgroundTexture[11]);
		textInfo.setString("They were able to fix the ship, but suddenly, an accident occurred,\nkilling all three of the crew members.");
		textInfo2.setString("\nWhat a disaster, we can't afford to lose a big portion of our crew.");
	}
	else if (outcomeType == lastFail) {
		background.setTexture(&backgroundTexture[5]);
		textInfo.setString("You watch the ship floating away,\nslowly fading into black.");
		textInfo2.setString("\n      \"This is it huh...\",\nyou usher out before joining the endless void.");
	}
	else if (outcomeType == lastSuccess) {
		background.setTexture(&backgroundTexture[7]);
		textInfo.setString("You were able to repair the ship and barely get back in.");
		textInfo2.setString("There isn't much hope left, its only a matter of timer\nbefore the end comes.");
	}
	else if (outcomeType == veerFail) {
		background.setTexture(&backgroundTexture[9]);
		textInfo.setString("You storage is already been sucked dry. ");
		textInfo2.setString("We won't be able to continue the journey,\nthis is the end...");
	}
    else if (outcomeType == veerFail2) {
		background.setTexture(&backgroundTexture[9]);
		textInfo.setString("You try to navigate back to main course.");
		textInfo2.setString("It's no use, we are lost forever.");
    }
	else if (outcomeType == veerSuccess) {
		background.setTexture(&backgroundTexture[8]);
		textInfo.setString("You recognized a cluster of asteroids\nand made it back to the main course.");
		textInfo2.setString("\nWell done captain.");
	}
	else if (outcomeType == veerSuccess2) {
		background.setTexture(&backgroundTexture[5]);
		textInfo.setString("You hand over your gold, disgusted by the shady practices ");
		textInfo2.setString("brought from intergalactic capitalism.");
	}
	else if (outcomeType == suckSuccess) {
		background.setTexture(&backgroundTexture[14]);
		textInfo.setString("Congrats!\nYour efforts have paid off.");
		textInfo2.setString("\nYou escaped and sustained minimal damaged.");
	}
	else if (outcomeType == suckFail) {
		background.setTexture(&backgroundTexture[13]);
		textInfo.setString("WARNING!!! WARNING!!!\nWe couldnt get enough power to escape unscathed.");
		textInfo2.setString("\nWe lost 4 crew members.");
	}
	else if (outcomeType == suckFail2) {
		background.setTexture(&backgroundTexture[13]);
		textInfo.setString("WARNING!!! WARNING!!!\nWe couldnt get enough power to escape.");
		textInfo2.setString("\nWe crashed into the planet, and there are no survivors.");
	}
}

void OutcomeState::update(const float dt) {
	timeIncrement(dt);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer > 0.25){

        game->pop_state(2);
        clickTimer = 0;
	}
}

