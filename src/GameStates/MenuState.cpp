#include "GameState.h"

using namespace Resource;

MenuState::MenuState(Game* game, int buttonNum, sf::Vector2f pos): numButtons(buttonNum){
    // Music
    music[1].stop();
    music[0].play();

    // Title
    title.setFont(font[2]);
    title.setFillColor(sf::Color::White);

    //Buttons
    sf::Text text;
    for (int i = 0; i < numButtons; i++){
        buttons.push_back(text);
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(pos.x, pos.y + i * 150);
        buttons[i].setCharacterSize(100);
        buttons[i].setFillColor(sf::Color::White);
    }
    // Set Game
    this->game = game;
}

void MenuState::handle_input(){
    // Create Event
    sf::Event event;

    while (game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
        /* Change Between game states */
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->window.close();
            else if (event.key.code == sf::Keyboard::Return)
                game->push_state(new PlayState(game, game->player1));
            break;
        //check if text is hovered over
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

void MenuState::draw(){
    // Background
    game->window.clear();
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    background.setTexture(&backgroundTexture[0]);

    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    game->view.setCenter(view.getCenter());
    game->window.setView(view);

    // Draw Background
    game->window.draw(background);

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);

    if(fadeTimer < 6)
        fadeIn(5);
}

bool MenuState::isTextClicked(sf::Text text){
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height + 20);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}
