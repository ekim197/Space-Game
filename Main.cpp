#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collision.h"

const float VIEW_WIDTH = 2048.0f;
const float VIEW_HEIGHT = 1152.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view);

int main(){
    // Create window
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH,VIEW_HEIGHT), "Coc Invaders", sf::Style::Default);

    // Create a View
    sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

    // Create Textures
    sf::Texture playerTexture, asteroidTexture;
    Collision::CreateTextureAndBitmask(playerTexture, "resources/Space_Ship.png");
    Collision::CreateTextureAndBitmask(asteroidTexture, "resources/Asteroid1.png");

    // Create Player
    Player body(&playerTexture, sf::Vector2f(1024.0f,700.0f), 0.03f);

    // Create Objects
    Asteroid ast1(&asteroidTexture, sf::Vector2f(1000.0f,0.0f), .01);

    // Start the Display
    while(window.isOpen()){

        // Checks for window polls
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:                     // Close
                    window.close();
                    break;
                case sf::Event::Resized:                    // Resized
                    resizeView(window, view);
                    break;
                case sf::Event::EventType::LostFocus:       // LostFocus
                    std::cout << "Lost Focus\n";
                    break;
                case sf::Event::EventType::GainedFocus:     // GainedFocus
                    std::cout << "Gained Focus\n";
                    break;
                default:
                    break;
            }
        }

        // Actions
        body.update();
        ast1.rotate();
        view.setCenter(sf::Vector2f(VIEW_WIDTH/2, body.getPosition().y - VIEW_HEIGHT/3));

        // Collision detection
        if(Collision::PixelPerfectTest(body.getBody(), ast1.getBody()))
            std::cout << "Collision detected\n";

        // Clear window
        window.clear(sf::Color(20,20,20));
        window.setView(view);
        ast1.draw(window);
        body.draw(window);
        window.display();
    }
    return 0;
}

void resizeView(const sf::RenderWindow& window, sf::View& view){
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
