#include "Game.h"
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Collision.h"
#include "Sound_.h"

Game::Game(){
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Endless Void", sf::Style::Close | sf::Style::Titlebar);
    setup();
}

Game::~Game(){
    while(!states.empty())
        pop_state();
}

Gamestate* Game::current_state(){
    if(states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::push_state(Gamestate* state){
    states.push_back(state);
}

void Game::pop_state(){
    states.back();
    delete states.back();
    states.pop_back();
}

void Game::game_loop(){
    sf::Clock clock;
    float dt = 0.0f;

    while (window.isOpen()){
        // Time Manipuation
        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();

        // RNG Mainpulation
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
    if(!buffer.loadFromFile("resources/Ship_Explosion.wav")){
        std::cerr << "Ship_Explosion.wav failed to load\n";
        exit(1);
    }
    sound.setBuffer(buffer);

    // Music
    if(!music[0].openFromFile("resources/Cosmic-Switchboard.ogg")){
        std::cerr << "Cosmic-Switchboard.ogg failed to load\n";
        exit(1);
    }
    if(!music[1].openFromFile("resources/Theyre-Here.ogg")){
        std::cerr << "Theyre-Here.ogg failed to load\n";
        exit(1);
    }
    music[0].setLoop(true);
    music[1].setLoop(true);

    // Create Player
    if(!Collision::CreateTextureAndBitmask(playerTexture[0], "resources/Space_Ship_Main_Body.png")){
        std::cerr << "Space_Ship0.png failed to load\n";
        exit(2);
    }
    if(!Collision::CreateTextureAndBitmask(playerTexture[1], "resources/Space_Ship_Left_Wing.png")){
        std::cerr << "Space_Ship1.png failed to load\n";
        exit(2);
    }
    if(!Collision::CreateTextureAndBitmask(playerTexture[2], "resources/Space_Ship_Right_Wing.png")){
        std::cerr << "Space_Ship2.png failed to load\n";
        exit(2);
    }
    if(!playerTexture[3].loadFromFile("resources/explosion.png")){
        std::cerr << "Space_Ship_explosion.png failed to load\n";
        exit(2);
    }
    player1 = Player(playerTexture, sf::Vector2u(9,9), sf::Vector2f(VIEW_WIDTH/2, 0.0f), 0.02f, 15, 0);

    // Create Collision Textures
    if(!Collision::CreateTextureAndBitmask(asteroidTexture, "resources/Asteroids.png")){
        std::cerr << "Asteroids.png failed to load\n";
        exit(3);
    }
    if(!Collision::CreateTextureAndBitmask(planetTexture, "resources/Planets.png")){
        std::cerr << "Planets.png failed to load\n";
        exit(4);
    }
    if(!Collision::CreateTextureAndBitmask(coinTexture, "resources/coin.png")){
        std::cerr << "coin.png failed to load\n";
        exit(5);
    }

    // Create Fonts
    if(!font[0].loadFromFile("resources/Mont-Heavy.otf")){
        std::cerr << "Mont-Heavy.otf failed to load\n";
        exit(5);
    }
    if(!font[1].loadFromFile("resources/Doctor-Glitch.otf")){
        std::cerr << "Doctor-Glitch.otf failed to load\n";
        exit(5);
    }
    if(!font[2].loadFromFile("resources/Glitch-City.ttf")){
        std::cerr << "GlitchCity.ttf failed to load\n";
        exit(5);
    }
}
