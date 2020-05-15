#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"

const float VIEW_WIDTH = 2048.0f;
const float VIEW_HEIGHT = 1152.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view);

int main(){
    // Create window
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH,VIEW_HEIGHT), "Coc Invaders", sf::Style::Default);

    // Create a View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

    // Create a Player
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Space_Ship.png");
    Entity body(&playerTexture, sf::Vector2f(200.0f, 200.0f), 0.03f);
    Entity body1(nullptr, sf::Vector2f(200.0f, 200.0f), 0.03f);

    // Create Objects
    sf::RectangleShape object1(sf::Vector2f(200.0f, 200.0f));
    object1.setFillColor(sf::Color::Red);
    object1.setPosition(sf::Vector2f(1000.0f,0.0f));
    sf::CircleShape object2(100);
    object2.setFillColor(sf::Color::Green);
    object2.setPosition(sf::Vector2f(1000.0f,0.0f));

    // Start the Display
    while(window.isOpen()){
        sf::Event event;

        // Checks for window polls
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    resizeView(window, view);
                    break;
                default:
                    break;
            }
        }

        body.update();
        body1.update();

        view.setCenter(sf::Vector2f(VIEW_WIDTH/2, body.getPosition().y - VIEW_HEIGHT/3));

        // Clear window
        window.clear();
        // Display
        window.setView(view);
        window.draw(object1);
        body1.draw(window);
        body.draw(window);
        window.draw(object2);
        window.display();
    }
    return 0;
}

void resizeView(const sf::RenderWindow& window, sf::View& view){
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
