#include <SFML\Graphics.hpp>
#include "Gamestate.h"
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif
using namespace Resource;

OutcomeState::OutcomeState(Game* game, PlayState* prev, int type) : prevState(prev), outcomeType(type) {
	// Push Game
	this->game = game;

	// Background
	background.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT * 2 / 3));

	// Text
	textInfo.setFont(font[4]);
	textInfo.setPosition(200, 825);
	textInfo.setCharacterSize(50); // in pixels, not points!
	textInfo.setFillColor(sf::Color::White);

	textInfo2.setFont(font[4]);
	textInfo2.setPosition(300, 875);
	textInfo2.setCharacterSize(50); // in pixels, not points!
	textInfo2.setFillColor(sf::Color::White);

	sf::Text textOption1; //text for choices button
	textOption1.setFont(font[3]);
	textOption1.setPosition(400, 1000);
	textOption1.setCharacterSize(35); // in pixels, not points!
	textOption1.setFillColor(sf::Color::White);

	for (int i = 0; i < 2; i++) {
		choiceButtons.push_back(textOption1);
		choiceButtons[i].setPosition(textOption1.getPosition().x, textOption1.getPosition().y + i * 50);
	}
	choiceButtons[0].setString("");
	choiceButtons[1].setString("Click here to continue");
	if (outcomeType == astSuccess) {
		background.setTexture(&backgroundTexture[4]);
		textInfo.setString("Your crew draw sticks, the person who drew the shortest stick\nlooked miserable.");
		textInfo2.setString("\nThe ship restarts, and we watched his lifeless body \nas we continue onward.Hopefully his sacrifice won't be in vain");
	}
	else if (outcomeType == astSuccess2) {
		background.setTexture(&backgroundTexture[6]);
		textInfo.setString("They were able to fix the ship and all get back in one piece.");
		textInfo2.setString("Lets hope our luck continues");
	}
	else if (outcomeType == astFail) {
		background.setTexture(&backgroundTexture[11]);
		textInfo.setString("They were able to fix the ship, but suddenly, an accident occurred,\nkilling all three of the crew members");
		textInfo2.setString("\nWhat a disaster, we can't afford to lose a big portion of our crew.");
	}
	else if (outcomeType == lastFail) {
		background.setTexture(&backgroundTexture[5]);
		textInfo.setString("You watch the ship floating, and slowly fade into black.");
		textInfo2.setString("\"This is it huh...\", you usher out before joining the endless void.");
	}
	else if (outcomeType == lastSuccess) {
		background.setTexture(&backgroundTexture[7]);
		textInfo.setString("You were able to repair the ship and barely get back in.");
		textInfo2.setString("How much longer will you be able to last");
	}
	else if (outcomeType == veerFail) {
		background.setTexture(&backgroundTexture[9]);
		textInfo.setString("You storage is already been sucked dry ");
		textInfo2.setString("We won't be able to continue the journey, this is the end ");
	}
	else if (outcomeType == veerSuccess) {
		background.setTexture(&backgroundTexture[8]);
		textInfo.setString("You used the asteroids as a guide and made it back to the main course. ");
		textInfo2.setString("Well done captain.");
	}
	else if (outcomeType == veerSuccess2) {
		background.setTexture(&backgroundTexture[5]);
		textInfo.setString("You hand over your wallet, disgusted by the shady practices ");
		textInfo2.setString("brought from intergalactic capitalism (lose 10 gold)");
	}
    else if (outcomeType == veerFail2) {
		background.setTexture(&backgroundTexture[9]);
		textInfo.setString("You try to navigate your way out");
		textInfo2.setString("But its no use. We are lost forever... (Lose all your crew)");
	}
	else if (outcomeType == suckSuccess) {
		background.setTexture(&backgroundTexture[14]);
		textInfo.setString("Congrats! Your efforts have paid off ");
		textInfo2.setString("and you will successfully return to space.");
	}
	else if (outcomeType == suckFail) {
		background.setTexture(&backgroundTexture[13]);
		textInfo.setString("Unfortunately, your efforts were not good enough.");
		textInfo2.setString("You will suffer consequences.");
	}

}

void OutcomeState::handle_input() {
	sf::Event event;

	while (game->window.pollEvent(event)) {
		switch (event.type) {
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

void OutcomeState::draw() {
	// Set View
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	view.setCenter(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
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
	if (fadeTimer <= 3)
		fadeIn();
}

void OutcomeState::update(const float dt) {
	timeIncrement(dt);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer > 0.25){
        game->pop_state(2);
        clickTimer = 0;
	}
}

