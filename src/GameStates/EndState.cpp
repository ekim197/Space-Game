#include "GameState.h"

using namespace Resource;

EndState::EndState(Game* game, PlayState* prev): PauseState(game, prev){
    // Title
    title.setPosition(100, game->view.getCenter().y - VIEW_HEIGHT/2 + 100);
    title.setString("GAMEOVER");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(100, 750 + i * 150);
        buttons[i].setCharacterSize(100);
        buttons[i].setFillColor(sf::Color::White);
    }

    int i = 0;
    for(auto& key: buttons)
        key.setPosition(100, game->view.getCenter().y - VIEW_HEIGHT/2 + 750 + i++ * 100);

    buttons[0].setString("");
    buttons[1].setString("MENU");

    game->gamePlayer.setGold(prev->player.getGold());
}
