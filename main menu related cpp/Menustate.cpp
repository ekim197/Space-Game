#include "Menustate.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Gamestate.h"
#include "PlayState.h"
#include "StoreState.h"

Menustate::Menustate(Game* game)
{


    //Text stuff
    sf::Text text;
    font.loadFromFile("D:/Design/C++ CIS29/SFML Test/Amatic-Bold.ttf");
    text.setFont(font);
    text.setPosition(100, 100);
    text.setCharacterSize(55); // in pixels, not points!
    //text.setColor(sf::Color::White);   // set the color
    text.setStyle(sf::Text::Bold); // set the text style

    //set positions of things
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x, text.getPosition().y + i * 100);
    }

    //Since it's only 3 text its fine to just manually set each...
    buttons[0].setString("Play Game");
    buttons[1].setString("Store");
    buttons[2].setString("Quit");


    this->game = game;
}

Menustate::~Menustate()
{
    //dtor
}

void Menustate::handle_input()
{
    sf::Event event;

    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
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
                buttons[0].setColor(sf::Color::Red);
            else
                buttons[0].setColor(sf::Color::White);
            if (isTextClicked(buttons[1]))
                buttons[1].setColor(sf::Color::Red);
            else
                buttons[1].setColor(sf::Color::White);
            if (isTextClicked(buttons[2]))
                buttons[2].setColor(sf::Color::Red);
            else
                buttons[2].setColor(sf::Color::White);
            break;

        default:
            break;


        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (isTextClicked(buttons[0]))
            load_game();
        else if(isTextClicked(buttons[1]))
            load_store();
        else if (isTextClicked(buttons[2]))
            game->window.close();


    }
}

void Menustate::update(const float dt)
{

}

void Menustate::draw(const float dt)
{
    sf::RectangleShape background(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("D:/Design/C++ CIS29/background_temp.png");
    background.setTexture(&backgroundTexture);

    game->window.draw(background);

    for (auto x : buttons)
        game->window.draw(x);

}

void Menustate::load_game()
{

    game->push_state(new PlayState(game));

}

void Menustate::load_store()
{
    game->push_state(new StoreState(game));
}

bool Menustate::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;


    //Otherwise, don't do anything
    return false;
}
