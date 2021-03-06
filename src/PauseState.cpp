#include "GameState.h"

using namespace Resource;

PauseState::PauseState(Game* game, GameState* prev): MenuState(game, 3), prevState(prev){
    // Title
    title.setPosition(VIEW_WIDTH/20.0, game->topView() + VIEW_HEIGHT/20.0);
    title.setString("ENDLESS\n    PAUSE");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(VIEW_WIDTH/20.0, game->topView() + VIEW_HEIGHT * 3.0/5.0 + i * 100.0 * VIEW_RATIO);
        buttons[i].setCharacterSize(75.0 * VIEW_RATIO);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[0].setString("CONTINUE");
    buttons[1].setString("OPTIONS");
    buttons[2].setString("MENU");
}

void PauseState::handle_input(){
    // Create Event
    sf::Event event;

    while(game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
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
    // Key input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& clickTimer >= 0.2)
        game->pop_state();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)&& clickTimer >= 0.2)
        game->pop_state();
}

void PauseState::update(const float dt){
    // Fade
    timeIncrement(dt);

    // Click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if(isTextClicked(buttons[0]))
            game->pop_state();
        else if(isTextClicked(buttons[1]))
            game->push_state(new OptionState(game, game->current_state()));
        else if(isTextClicked(buttons[2]))
            game->backToMainState();
    }
}

void PauseState::draw(){
    // Set Rect
    sf::RectangleShape rect(sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    rect.setFillColor(sf::Color(30,30,30,150));
    rect.setPosition(0, game->topView());

    // Draw Background
    game->window.clear();
    prevState->draw();
    game->window.draw(rect);

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}

