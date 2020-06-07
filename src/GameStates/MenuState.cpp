#include "GameState.h"

using namespace Resource;

MenuState::MenuState(Game* game){
    // Music
    music[1].stop();
    music[0].play();

    // Text
    title.setFont(font[2]);
    title.setPosition( 800, 100);
    title.setCharacterSize(200); // in pixels, not points!
    title.setFillColor(sf::Color::White);   // set the color
    title.setString("ENDLESS\n    VOID");

    sf::Text text;
    text.setFont(font[0]);
    text.setPosition(100, 550);
    text.setCharacterSize(100); // in pixels, not points!
    text.setFillColor(sf::Color::White);   // set the color

    //Set positions of buttons
    for (int i = 0; i < NUM_BUTTONS; i++){
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x, text.getPosition().y + i * 150);
    }
    buttons[0].setString("PLAY GAME");
    buttons[1].setString("TUTORIAL");
    buttons[2].setString("STORE");
    buttons[3].setString("QUIT");

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
                game->push_state(new PlayState(game));
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

void MenuState::update(const float dt){
    fadeTimer += dt;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt != 0){
        if (isTextClicked(buttons[0]))
            game->push_state(new PlayState(game));
        else if(isTextClicked(buttons[1]))
            game->push_state(new TutorialState(game));
        else if (isTextClicked(buttons[2]))
            game->push_state(new StoreState(game));
        else if (isTextClicked(buttons[3]))
            game->window.close();
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
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}
