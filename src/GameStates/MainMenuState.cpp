#include "GameState.h"

using namespace Resource;

MainMenuState::MainMenuState(Game* game) : MenuState(game, 5, sf::Vector2f(100,550)){
    // Title
    title.setPosition(800,100);
    title.setCharacterSize(200); // in pixels, not points!
    title.setString("ENDLESS\n    VOID");

    // Buttons
    buttons[4].setFont(font[0]);
    buttons[4].setPosition(1500, 650 );
    buttons[4].setCharacterSize(60); // in pixels, not points!
    buttons[4].setFillColor(sf::Color::White);   // set the color

    buttons[0].setString("PLAY GAME");
    buttons[1].setString("TUTORIAL");
    buttons[2].setString("STORE");
    buttons[3].setString("QUIT");
    buttons[4].setString(".");
}

void MainMenuState::update(const float dt){
    fadeTimer += dt;
    timer += dt;

    if(timer >= 0.50){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt != 0){
            if (isTextClicked(buttons[0]))
                game->push_state(new PlayState(game, game->player1));
            else if(isTextClicked(buttons[1]))
                game->push_state(new TutorialState(game));
            else if (isTextClicked(buttons[2]))
                game->push_state(new StoreState(game));
            else if (isTextClicked(buttons[3]))
                game->window.close();
            else if (isTextClicked(buttons[4]))
                game->push_state(new BackdoorState(game));
        }
    }
}
