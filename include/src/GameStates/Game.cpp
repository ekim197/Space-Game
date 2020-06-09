#include "Game.h"
#include <iostream>

using namespace Resource;

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
        rng = abs(rng);

        // Exception handling
        if (current_state() == nullptr)
            continue;
        current_state()->handle_input();
        current_state()->update(dt);

        current_state()->draw();
        window.display();
    }
}

void Game::setup(){
    // Create a View
    view = sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

    // Sound Stuff
    if(!bufferTEMP.loadFromFile(RESOURCE_PATH + "Audio/Ship_Explosion.wav")){
        std::cerr << "Ship_Explosion.wav failed to load\n";
        exit(1);
    }
    sound.setBuffer(bufferTEMP);

    // Music
    if(!music[0].openFromFile(RESOURCE_PATH + "Audio/Cosmic-Switchboard.ogg")){
        std::cerr << "Cosmic-Switchboard.ogg failed to load\n";
        exit(1);
    }
    if(!music[1].openFromFile(RESOURCE_PATH + "Audio/Theyre-Here.ogg")){
        std::cerr << "Theyre-Here.ogg failed to load\n";
        exit(1);
    }
    music[0].setLoop(true);
    music[1].setLoop(true);
    try{
        // Create Player
        makeCollisionTexture(playerTexture[0], "Ship_Sprite/Main_Body.png");
        makeCollisionTexture(playerTexture[1], "Ship_Sprite/Main_Left_Wing.png");
        makeCollisionTexture(playerTexture[2], "Ship_Sprite/Main_Right_Wing.png");
        makeCollisionTexture(playerTexture[3], "Ship_Sprite/Damaged_Left_Wing.png");
        makeCollisionTexture(playerTexture[4], "Ship_Sprite/Damaged_Right_Wing.png");
        makeTexture(playerTexture[5], "Ship_Sprite/Status_Main_Body.png");
        makeTexture(playerTexture[6], "Ship_Sprite/Status_Left_Wing.png");
        makeTexture(playerTexture[7], "Ship_Sprite/Status_Right_Wing.png");
        makeTexture(playerTexture[8], "Ship_Sprite/explosion.png");

        defaultPlayer = Player(playerTexture, sf::Vector2u(9,9), sf::Vector2f(VIEW_WIDTH/2, 0.0), 8, 15, 0);
        gamePlayer = defaultPlayer;

        // Create Entity Textures
        makeCollisionTexture(asteroidTexture, "Entity_Sprite/Asteroids.png");
        makeCollisionTexture(planetTexture, "Entity_Sprite/Planets.png");
        makeCollisionTexture(coinTexture, "Entity_Sprite/Coin.png");
        makeCollisionTexture(warZoneTexture, "Entity_Sprite/War_Zone.png");

        // Create Backround Textures
        makeTexture(backgroundTexture[0], "Background/Menu_Bg.png");
        makeTexture(backgroundTexture[1], "Background/Play_Bg.png");
        makeTexture(backgroundTexture[2], "Background/Store_Bg.png");
        makeTexture(backgroundTexture[3], "Background/Event1_Bg.png");
        makeTexture(backgroundTexture[4], "Background/Event2_Bg.png");
        makeTexture(backgroundTexture[5], "Background/Event3_Bg.png");

        // Create Fonts
        makeFont(font[0], "Font/Mont-Heavy.otf");
        makeFont(font[1], "Font/Doctor-Glitch.otf");
        makeFont(font[2], "Font/Glitch-City.ttf");
        makeFont(font[3], "Font/Roboto-Italic.ttf");
        makeFont(font[4], "Font/Roboto-Black.ttf");

    }
    catch(const std::string& error){
        std::cerr << "\n\n" << error << " failed to load\nSee if the file is missing or mispelled\n\n";
        exit(1);
    }
}

void Game::makeCollisionTexture(sf::Texture& text, std::string file){
    if(!Collision::CreateTextureAndBitmask(text, RESOURCE_PATH + file))
        throw file;
}

void Game::makeTexture(sf::Texture& text, std::string file){
    if(!text.loadFromFile(RESOURCE_PATH + file))
        throw file;
}

void Game::makeFont(sf::Font& font, std::string file){
    if(!font.loadFromFile(RESOURCE_PATH + file))
        throw file;
}





