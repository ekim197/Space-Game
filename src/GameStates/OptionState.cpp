#include "GameState.h"

using namespace Resource;

OptionState::OptionState(Game* game, GameState* prev): MenuState(game, 3), prevState(prev){
    // Title
    title.setPosition(100, game->view.getCenter().y - VIEW_HEIGHT/2 + 100);
    title.setString("OPTIONS");

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

    buttons[0].setString("CHANGE RESOLUTION");
    buttons[1].setString("MUTE MUSIC");
    buttons[2].setString("BACK");

}

void OptionState::handle_input(){
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

void OptionState::update(const float dt){
    // Fade
    timeIncrement(dt);

    // Click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if(isTextClicked(buttons[0]))
            std::cout << "Resolution Changed";
        else if(isTextClicked(buttons[1]))
            std::cout << "Mute Music";
        else if(isTextClicked(buttons[2]))
            game->pop_state();


        clickTimer = 0;
    }
}

void OptionState::draw(){
    // Set rect
    sf::RectangleShape rect(sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    rect.setFillColor(sf::Color(30,30,30,230));
    rect.setPosition(0, game->view.getCenter().y - VIEW_HEIGHT/2);

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

