#include "GameState.h"

using namespace Resource;

MainMenuState::MainMenuState(Game* game) : MenuState(game, 5){
	//Sound
	soundList.stopAllSounds();
	soundList.playSound(RESOURCE_PATH + "Audio/MainMenu.ogg");

    // Title
    title.setPosition(800,100);
    title.setCharacterSize(200); // in pixels, not points!
    title.setString("ENDLESS\n    VOID");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(100, 550 + i * 150);
        buttons[i].setCharacterSize(100);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[4].setFont(font[0]);
    buttons[4].setPosition(2000, 1050);
    buttons[4].setCharacterSize(20); // in pixels, not points!
    buttons[4].setFillColor(sf::Color(229, 245, 249));   // set the color

    buttons[0].setString("PLAY GAME");
    buttons[1].setString("TUTORIAL");
    buttons[2].setString("STORE");
    buttons[3].setString("QUIT");
    buttons[4].setString(".");
}

void MainMenuState::update(const float dt){
    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.50){
        if (isTextClicked(buttons[0]))
            game->push_state(new PlayState(game, game->gamePlayer));
        else if(isTextClicked(buttons[1]))
            game->push_state(new TutorialState(game));
        else if (isTextClicked(buttons[2]))
            game->push_state(new StoreState(game));
        else if (isTextClicked(buttons[3]))
            game->window.close();
        else if (isTextClicked(buttons[4]))
            game->push_state(new BackdoorState(game));
        //clickTimer = 0;
    }
}
