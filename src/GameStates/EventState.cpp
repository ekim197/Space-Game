#include <SFML\Graphics.hpp>
#include "Gamestate.h"

EventState::EventState(Game* game, int type): eventType(type){
    // Push Game
    this->game = game;

    // Music
    game->music[0].stop();
    game->music[1].play();

    // Background
    background.setSize(sf::Vector2f(VIEW_WIDTH * 2 / 3, VIEW_HEIGHT * 2 / 3));
    background.setOrigin(background.getGlobalBounds().width / 2, 0);
    background.setPosition(VIEW_WIDTH / 2, 50);

    // Text
    font1.loadFromFile("resources/Roboto-Italic.ttf"); //font for choices button
    font2.loadFromFile("resources/Roboto-Black.ttf"); // font for event information


    textInfo.setFont(font2);
    textInfo.setPosition(300, 825);
    textInfo.setCharacterSize(50); // in pixels, not points!
    textInfo.setFillColor(sf::Color::White);

    textInfo2.setFont(font2);
    textInfo2.setPosition(400, 875);
    textInfo2.setCharacterSize(50); // in pixels, not points!
    textInfo2.setFillColor(sf::Color::White);

    sf::Text textOption1; //text for choices button
    textOption1.setFont(font1);
    textOption1.setPosition(400, 1000);
    textOption1.setCharacterSize(35); // in pixels, not points!
    textOption1.setFillColor(sf::Color::White);

    for (int i = 0; i < 2; i++){
        choiceButtons.push_back(textOption1);
        choiceButtons[i].setPosition(textOption1.getPosition().x, textOption1.getPosition().y + i * 50);
    }

    if(eventType == 1){
        backgroundTexture.loadFromFile("resources/event1.png");
        background.setTexture(&backgroundTexture);

        textInfo.setString("You crashed and the main hull is breached,");
        textInfo2.setString("someone is going to have to fix it, but its dangerous...");

        choiceButtons[0].setString("Option 1: Sacrifice 1 person(guarentee to lose on passenger)");
        choiceButtons[1].setString("Option 2: Risk 3 people(60% chance they all survive)");
    }
    else if(eventType == 2){
        backgroundTexture.loadFromFile("resources/event2.png");
        background.setTexture(&backgroundTexture);

        textInfo.setString("You are the last person on the ship, and the ship won't fix ");
        textInfo2.setString("itself, There is no options left, you must fix the ship:");

        choiceButtons[0].setString("");
        choiceButtons[1].setString("");
    }
    else if(eventType == 3){
        backgroundTexture.loadFromFile("resources/event3.png");
        background.setTexture(&backgroundTexture);

        textInfo.setString("Your ship has veered off course. You can use the");
        textInfo2.setString("              findYourWayBack module by EngiAtom(EA) ");

        choiceButtons[0].setString("Option 1: Try to figure it out yourself(What's the worst that could happen)");
        choiceButtons[1].setString("Option 2: Pay 3 gold to use the module (guarantee to get back)");
    }
}

void EventState::handle_input(){
    sf::Event event;

    while (game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
        //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->push_state(new MenuState(game));
            break;
        case sf::Event::MouseMoved:
            if (isTextClicked(choiceButtons[0]))
                choiceButtons[0].setFillColor(sf::Color::Red);
            else
                choiceButtons[0].setFillColor(sf::Color::White);
            if (isTextClicked(choiceButtons[1]))
                choiceButtons[1].setFillColor(sf::Color::Red);
            else
                choiceButtons[1].setFillColor(sf::Color::White);
        default:
            break;
        }
    }
}

void EventState::draw(){
    // Set View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH/2, VIEW_HEIGHT/2);

    // Draws the Buttons
    for (auto x : choiceButtons)
        game->window.draw(x);

    game->window.setView(view);
    game->window.draw(background);
    game->window.draw(textInfo);
    game->window.draw(textInfo2);
}

void EventState::update(const float dt){

}

bool EventState::isTextClicked(sf::Text text){
    float x = text.getPosition().x;
    float y = text.getPosition().y;
    float width = text.getGlobalBounds().width;
    float height = text.getGlobalBounds().height;
    sf::IntRect rect(x, y, width, height);
    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    //Otherwise, don't do anything
    return false;
}
