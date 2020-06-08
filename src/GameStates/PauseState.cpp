#include "GameState.h"

using namespace Resource;

PauseState::PauseState(Game* game): MenuState(game, 3){
    buttons[0].setString("CONTINUE");
    buttons[1].setString("MENU");
    buttons[2].setString("MENU");
}

void PauseState::handle_input(){
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
                game->push_state(new MainMenuState(game));
            else if (event.key.code == sf::Keyboard::Return)
                game->pop_state();
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

void PauseState::update(const float dt){
    fadeTimer += dt;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt != 0){
        if (isTextClicked(buttons[0]))
            game->pop_state();
        else if (isTextClicked(buttons[1]))
            game->push_state(new MainMenuState(game));
        else if (isTextClicked(buttons[2]))
            game->push_state(new MainMenuState(game));
    }
}

void PauseState::draw(){
    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);
    game->view.setCenter(view.getCenter());
    game->window.setView(view);

    // Draw Background
    game->window.clear(sf::Color(30,30,30, 0));

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}
