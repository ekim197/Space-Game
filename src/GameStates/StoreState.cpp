#include "GameState.h"
#include <string>
#include <iomanip>
#include <sstream>

using namespace Resource;

StoreState::StoreState(Game* game): MenuState(game, 5){
    // Title
    title.setPosition(100,100);
    title.setCharacterSize(150); // in pixels, not points!
    title.setString("SPACE MECHANIC");

	//Sound 
	soundList.stopAllSounds();
	soundList.playSound(RESOURCE_PATH + "Audio/Store.ogg");

    // Buttons
    for (int i = 0; i < numButtons; i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(100, 550 + i * 100);
        buttons[i].setCharacterSize(75);
        buttons[i].setFillColor(sf::Color::White);
        buttons[i].setOutlineColor(sf::Color::Black);
        buttons[i].setOutlineThickness(4);
    }

    buttons[0].setString("Increase Speed");
    buttons[1].setString("Decrease Speed");
    buttons[2].setString("Increase Crew");
    buttons[3].setString("Decrease Crew");
    buttons[4].setString("Back");

    // Prices
    for (int i = 0; i < 4; i++){
        prices.push_back(sf::Text());
        prices[i].setFont(font[0]);
        prices[i].setPosition(900, 550 + i * 100);
        prices[i].setCharacterSize(75);
        prices[i].setFillColor(sf::Color::White);
        prices[i].setOutlineColor(sf::Color::Black);
        prices[i].setOutlineThickness(4);
    }
    prices[0].setString("Spend 10 gold");
    prices[1].setString("Spend 10 gold");
    prices[2].setString("Spend 10 gold");
    prices[3].setString("Sell for 5 gold");

    // Player Info
    for(int i = 0; i < 3; i++){
        playerInfo.push_back(sf::Text());
        playerInfo[i].setFont(font[0]);
        playerInfo[i].setPosition(VIEW_WIDTH - 500, 300 + i * 80);
        playerInfo[i].setCharacterSize(75);
        playerInfo[i].setFillColor(sf::Color::Yellow);
        playerInfo[i].setOutlineColor(sf::Color::Black);
        playerInfo[i].setOutlineThickness(4);
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
    timeIncrement(dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.50){
        if (isTextClicked(buttons[0]) && game->gamePlayer.getGold() >= 10){
            game->gamePlayer.setSpeed(game->gamePlayer.getSpeed() + 0.002);
            game->gamePlayer.loseGold(10);
        }
        else if(isTextClicked(buttons[1]) && game->gamePlayer.getGold() >= 10){
            game->gamePlayer.setSpeed(game->gamePlayer.getSpeed() - 0.002);
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
        else if (isTextClicked(buttons[4]))
            game->push_state(new MainMenuState(game));
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
