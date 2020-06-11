#include "GameState.h"
#include <string>
#include <iomanip>
#include <sstream>

using namespace Resource;

StoreState::StoreState(Game* game): MenuState(game, 5){
    // Title
    title.setPosition(VIEW_WIDTH/20.0, VIEW_HEIGHT/20.0);
    title.setCharacterSize(120.0 * VIEW_RATIO); // in pixels, not points!
    title.setString("SPACE\n   MECHANIC");
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(4.0 * VIEW_RATIO);

    // Buttons and Prices
    for (int i = 0; i < numButtons; i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(VIEW_WIDTH/20.0, VIEW_HEIGHT * 5.0/12.0 + i * 100.0 * VIEW_RATIO);
        buttons[i].setCharacterSize(75.0 * VIEW_RATIO);
        buttons[i].setFillColor(sf::Color::White);
        buttons[i].setOutlineColor(sf::Color::Black);
        buttons[i].setOutlineThickness(4.0 * VIEW_RATIO);
        prices.push_back(sf::Text());
        prices[i].setFont(font[0]);
        prices[i].setPosition(VIEW_WIDTH/2.0, VIEW_HEIGHT * 5.0/12.0  + i * 100.0 * VIEW_RATIO);
        prices[i].setCharacterSize(75.0 * VIEW_RATIO);
        prices[i].setFillColor(sf::Color::White);
        prices[i].setOutlineColor(sf::Color::Black);
        prices[i].setOutlineThickness(4.0 * VIEW_RATIO);
    }

    buttons[0].setString("Increase Speed");
    buttons[1].setString("Decrease Speed");
    buttons[2].setString("Increase Crew");
    buttons[3].setString("Decrease Crew");
    buttons[4].setString("Back");
    prices[0].setString("Spend 10 gold");
    prices[1].setString("Spend 10 gold");
    prices[2].setString("Spend 10 gold");
    prices[3].setString("Sell for 5 gold");

    // Player Info
    for(int i = 0; i < 3; i++){
        playerInfo.push_back(sf::Text());
        playerInfo[i].setFont(font[0]);
        playerInfo[i].setPosition(VIEW_WIDTH * 13.0/20.0, VIEW_HEIGHT/20.0 + i * 80 * VIEW_RATIO);
        playerInfo[i].setCharacterSize(75.0 * VIEW_RATIO);
        playerInfo[i].setFillColor(sf::Color::Yellow);
        playerInfo[i].setOutlineColor(sf::Color::Black);
        playerInfo[i].setOutlineThickness(4.0 * VIEW_RATIO);
    }
}

void StoreState::handle_input(){
    sf::Event event;

    while (this->game->window.pollEvent(event)){
        switch (event.type){
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new MainMenuState(game));
            break;
        // Hovered Over Text
        case sf::Event::MouseMoved:
            for(auto& i : buttons){
                if(isTextClicked(i))
                    i.setFont(font[1]);
                else
                    i.setFont(font[0]);
            }
            break;
        default:
            break;
        }
    }
}

void StoreState::update(const float dt){
	//Sound
	if (!soundList.getStatusOfMusic(RESOURCE_PATH + "Audio/Store.ogg")) {
		soundList.stopAllSounds();
		soundList.playSound(RESOURCE_PATH + "Audio/Store.ogg");
	}
    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if (isTextClicked(buttons[0]) && game->gamePlayer.getGold() >= 10){
            game->gamePlayer.setSpeed(game->gamePlayer.getSpeed() + 0.2);
            game->gamePlayer.loseGold(10);
        }
        else if(isTextClicked(buttons[1]) && game->gamePlayer.getGold() >= 10){
            game->gamePlayer.setSpeed(game->gamePlayer.getSpeed() - 0.2);
            game->gamePlayer.loseGold(10);
        }
        else if (isTextClicked(buttons[2]) && game->gamePlayer.getGold() >= 10){
            game->gamePlayer.loseGold(10);;
            game->gamePlayer.gainCrew();
        }
        else if (isTextClicked(buttons[3]) && game->gamePlayer.getCrew() > 2){
            game->gamePlayer.gainGold(5);
            game->gamePlayer.loseCrew(2);
        }
        else if (isTextClicked(buttons[4])){
            game->backToMainState();
            clickTimer = 0; // Since it will return
            return;
        }
        clickTimer = 0;
    }

    playerInfo[0].setString("Gold: " + std::to_string(game->gamePlayer.getGold()));
    playerInfo[1].setString("Crew: " + std::to_string(game->gamePlayer.getCrew()));

    std::stringstream sout;
    sout << std::fixed << std::setprecision(0) << game->gamePlayer.getSpeed() * 1000;

    playerInfo[2].setString("Speed: " + sout.str());

}

void StoreState::draw(){
    // Background
    game->window.clear();
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    background.setTexture(&backgroundTexture[2]);

    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    game->view.setCenter(view.getCenter());
    game->window.setView(view);

    // Draw Background
    game->window.draw(background);

    // Draw Buttons
    for(auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);

    // Draw Prices
    for(auto key : prices)
        game->window.draw(key);

    // Draw Player Info
    for(auto key : playerInfo)
        game->window.draw(key);

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}
