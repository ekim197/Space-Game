#include "GameState.h"

using namespace Resource;

MenuState::MenuState(Game* game, int buttonNum): numButtons(buttonNum){
    // Music
    music[1].stop();
    music[0].play();

    // Title
    title.setFont(font[2]);
    title.setFillColor(sf::Color::White);

    //Buttons
    for (int i = 0; i < numButtons; i++)
        buttons.push_back(sf::Text());

    // Set Game
    this->game = game;
}

void MenuState::handle_input(){
    // Create Event
    sf::Event event;

    while (game->window.pollEvent(event)){
        switch (event.type){
        // Close the window
        case sf::Event::Closed:
            game->window.close();
            break;
        // Key is Pressed
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Return)
                game->push_state(new PlayState(game, game->gamePlayer));
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
        // Default
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

