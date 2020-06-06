#include "GameState.h"

StoreState::StoreState(Game* game){
    // Set Game
    this->game = game;
}

void StoreState::draw(){
    sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/store_temp.png");
    background.setTexture(&backgroundTexture);

    game->window.draw(background);
}

void StoreState::handle_input(){
    sf::Event event;

    while (this->game->window.pollEvent(event)){
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new MenuState(game));
            break;

        default:
            break;
        }
    }

}

void StoreState::update(const float dt){
    // Feature not in yet
    if(dt != 0){
        std::cout << dt << '\n';
    }
}
