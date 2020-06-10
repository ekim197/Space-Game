#include "GameState.h"

using namespace Resource;

MainMenuState::MainMenuState(Game* game) : MenuState(game, 6){
	//Sound
	soundList.stopAllSounds();
	soundList.playSound(RESOURCE_PATH + "Audio/MainMenu.ogg");

    // Title
    title.setPosition(800,100);
    title.setString("ENDLESS\n    VOID");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(100, 400 + i * 150);
        buttons[i].setCharacterSize(100);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[5].setFont(font[0]);
    buttons[5].setPosition(2000, 1050);
    buttons[5].setCharacterSize(40); // in pixels, not points!
    buttons[5].setFillColor(sf::Color(229, 245, 249));   // set the color

    buttons[0].setString("PLAY GAME");
    buttons[1].setString("TUTORIAL");
    buttons[2].setString("STORE");
    buttons[3].setString("Options");
    buttons[4].setString("QUIT");
    buttons[5].setString(".");
}

void MainMenuState::update(const float dt){
    //Sound
    if (!soundList.getStatusOfMusic(RESOURCE_PATH + "Audio/MainMenu.ogg")) {
        soundList.stopAllSounds();
        soundList.playSound(RESOURCE_PATH + "Audio/MainMenu.ogg");
    }

    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if (isTextClicked(buttons[0]))
            game->push_state(new PlayState(game, game->gamePlayer));
        else if(isTextClicked(buttons[1]))
            game->push_state(new TutorialState(game));
        else if (isTextClicked(buttons[2]))
            game->push_state(new StoreState(game));
/*
        else if (isTextClicked(buttons[3]))
            game->push_state(new OptionState(game));

*/
        else if (isTextClicked(buttons[4]))
            game->window.close();
        else if (isTextClicked(buttons[5]))
            game->push_state(new BackdoorState(game));
        clickTimer = 0;
    }
}
