#include "Game.h"
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Collision.h"
#include "Sound_.h"

Game::Game()
{
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Endless Void", sf::Style::Close | sf::Style::Titlebar);
    setup();
}

Game::~Game()
{
    while(!states.empty())
        pop_state();
}

Gamestate* Game::current_state()
{
    if(states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::push_state(Gamestate* state)
{
    states.push_back(state);
}

void Game::pop_state()
{
    states.back();
    delete states.back();
    states.pop_back();
}

void Game::game_loop()
{
    sf::Clock clock;
    float dt = 0.0f;

    while (window.isOpen()){
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();
        rng = elapsed.asMicroseconds();
        rng *= rng;
        rng *= (rng / 100); // about 17 digits

        // Exception handling
        if (current_state() == nullptr)
            continue;

        current_state()->handle_input();
        current_state()->update(dt);
        window.clear();
        current_state()->draw();
        window.display();
    }
}

void Game::setup(){
    // Create a View
    view = sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

    // Sound Stuff
    if(!buffer.loadFromFile("resources/Ship_Explosion.wav"))
        std::cout << "Sound failed to load\n";

    sound.setBuffer(buffer);

    // Create Player
    if(!Collision::CreateTextureAndBitmask(playerTexture[0], "resources/Space_Ship_Main_Body.png"))
        std::cout << "Space_Ship0 failed to load\n";
    if(!Collision::CreateTextureAndBitmask(playerTexture[1], "resources/Space_Ship_Left_Wing.png"))
        std::cout << "Space_Ship1 failed to load\n";
    if(!Collision::CreateTextureAndBitmask(playerTexture[2], "resources/Space_Ship_Right_Wing.png"))
        std::cout << "Space_Ship2 failed to load\n";
    if(!playerTexture[3].loadFromFile("resources/explosion.png"))
        std::cout << "Space_Ship_explosion failed to load\n";

    player1 = Player(playerTexture, sf::Vector2f(VIEW_WIDTH/2, 0), 1.5, 15, 0, sf::Vector2u(9,9));

    // Create Objects
    Collision::CreateTextureAndBitmask(asteroidTexture, "resources/Asteroids.png");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            asteroid[i][j] = Asteroid(&asteroidTexture, sf::Vector2f(1024, -600), sf::Vector2u(4,4), i, j, 2);
    }

    Collision::CreateTextureAndBitmask(planetTexture, "resources/Planets.png");
    for(int i = 0; i < 4; i++){
        planet[i] = Planet(&planetTexture, sf::Vector2f(0.0f,2300.0f), sf::Vector2u(4,1), i, 0, .001, 5);
    }

    Collision::CreateTextureAndBitmask(coinTexture, "resources/coin.png");
    coin = Coin(&coinTexture, sf::Vector2f(1500.0f,200.0f), sf::Vector2u(10,1));
}
