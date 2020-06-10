#include "GameState.h"

using namespace Resource;

PauseState::PauseState(Game* game, GameState* prev): MenuState(game, 2), prevState(prev){
    // Title
    title.setPosition(100, game->view.getCenter().y - VIEW_HEIGHT/2 + 100);
    title.setString("ENDLESS\n    PAUSE");

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

    buttons[0].setString("CONTINUE");
    buttons[1].setString("MENU");
}

void PauseState::handle_input(){
    // Create Event
    sf::Event event;
	// Check Key is Pressed
	
    while (game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
        /* Change Between game states */
       /* case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->pop_state();
            else if (event.key.code == sf::Keyboard::Return)
                game->pop_state();
            break;*/
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && clickTimer >= 0.2)
		game->pop_state();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && clickTimer >= 0.2)
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
            game->backToMainState();
        clickTimer = 0;
    }
}

void PauseState::draw(){
    // Set rect
    sf::RectangleShape rect(sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    rect.setFillColor(sf::Color(30,30,30,150));
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

bool PauseState::isTextClicked(sf::Text text) {
	sf::IntRect rect(text.getPosition().x, text.getPosition().y - (game->view.getCenter().y - VIEW_HEIGHT / 2), text.getGlobalBounds().width, text.getGlobalBounds().height + 20);

	if (rect.contains(sf::Mouse::getPosition(game->window)))
		return true;
	return false;
}