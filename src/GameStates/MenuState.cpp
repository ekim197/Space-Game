#include "GameState.h"

MenuState::MenuState(Game* game){
    // Music
    game->music[1].stop();
    game->music[0].play();

    // Text
    title.setFont(game->font[1]);
    title.setPosition( 800, 100);
    title.setCharacterSize(200); // in pixels, not points!
    title.setFillColor(sf::Color::White);   // set the color
    title.setString("ENDLESS\n    VOID");

    sf::Text text;
    text.setFont(game->font[0]);
    text.setPosition(100, 700);
    text.setCharacterSize(100); // in pixels, not points!
    text.setFillColor(sf::Color::White);   // set the color

    //Set positions of buttons
    for (int i = 0; i < NUM_BUTTONS; i++){
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x, text.getPosition().y + i * 150);
    }
    buttons[0].setString("PLAY GAME");
    buttons[1].setString("STORE");
    buttons[2].setString("QUIT");

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
                load_game();
            break;
        //check if text is hovered over
        case sf::Event::MouseMoved:
            if (isTextClicked(buttons[0]))
                buttons[0].setFont(game->font[1]);
            else
                buttons[0].setFont(game->font[0]);
            if (isTextClicked(buttons[1]))
                buttons[1].setFont(game->font[1]);
            else
                buttons[1].setFont(game->font[0]);
            if (isTextClicked(buttons[2]))
                buttons[2].setFont(game->font[1]);
            else
                buttons[2].setFont(game->font[0]);
            break;
        default:
            break;
        }
    }
}

void MenuState::update(const float dt){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt != 0){
        if (isTextClicked(buttons[0]))
            load_game();
        else if(isTextClicked(buttons[1]))
            load_store();
        else if (isTextClicked(buttons[2]))
            game->window.close();
    }
}

void MenuState::draw(){
    // Setup
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/background_temp.png");
    background.setTexture(&backgroundTexture);

    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);

    // Draw Background
    game->window.setView(view);
    game->window.draw(background);

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);
}

void MenuState::load_game(){
    game->push_state(new PlayState(game));
}

void MenuState::load_store(){
    game->push_state(new StoreState(game));
}

bool MenuState::isTextClicked(sf::Text text){
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}
