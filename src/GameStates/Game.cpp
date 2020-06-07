#include "Game.h"
#include <iostream>

Game::Game(){
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Endless Void", sf::Style::Close | sf::Style::Titlebar);
    setup();
}

Game::~Game(){
    while(!states.empty())
        pop_state();
}

GameState* Game::current_state(){
    if(states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::push_state(GameState* state){
    states.push_back(state);
}

void Game::pop_state(){
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
    try{
        // Create Player
        makeCollisionTexture(playerTexture[0], "resources/Ship_Sprite/Main_Body.png");
        makeCollisionTexture(playerTexture[1], "resources/Ship_Sprite/Main_Left_Wing.png");
        makeCollisionTexture(playerTexture[2], "resources/Ship_Sprite/Main_Right_Wing.png");
        makeCollisionTexture(playerTexture[3], "resources/Ship_Sprite/Damaged_Left_Wing.png");
        makeCollisionTexture(playerTexture[4], "resources/Ship_Sprite/Damaged_Right_Wing.png");
        makeTexture(playerTexture[5], "resources/Ship_Sprite/Status_Main_Body.png");
        makeTexture(playerTexture[6], "resources/Ship_Sprite/Status_Left_Wing.png");
        makeTexture(playerTexture[7], "resources/Ship_Sprite/Status_Right_Wing.png");
        makeTexture(playerTexture[8], "resources/Ship_Sprite/explosion.png");

        player1 = Player(playerTexture, sf::Vector2u(9,9), sf::Vector2f(VIEW_WIDTH/2, 0.0f), 0.02f, 15, 0);

        // Create Entity Textures
        makeCollisionTexture(asteroidTexture, "resources/Asteroids.png");
        makeCollisionTexture(planetTexture, "resources/Planets.png");
        makeCollisionTexture(coinTexture, "resources/coin.png");

        // Create Fonts
        makeFont(font[0], "resources/Mont-Heavy.otf");
        makeFont(font[1], "resources/Doctor-Glitch.otf");
        makeFont(font[2], "resources/Glitch-City.ttf");
    }
    catch(const std::string& error){
        std::cerr << "\n\n" << error << " failed to load\n\n\n";
        exit(1);
    }
}

void Game::makeCollisionTexture(sf::Texture& text, std::string file){
    if(!Collision::CreateTextureAndBitmask(text, file))
        throw file;
}

void Game::makeTexture(sf::Texture& text, std::string file){
    if(!text.loadFromFile(file))
        throw file;
}

void Game::makeFont(sf::Font& font, std::string file){
    if(!font.loadFromFile(file))
        throw file;
}
