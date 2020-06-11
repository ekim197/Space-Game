#include "Game.h"
#include <iostream>

using namespace Resource;

Game::Game() {
	window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Endless Void", sf::Style::Close | sf::Style::Titlebar);
	setup();
}

Game::~Game() {
	while (!states.empty())
		pop_state();
}

GameState* Game::current_state() {
	if (states.empty()) {
		return nullptr;
	}
	else
		return states.back();
}

void Game::push_state(GameState* state) {
	states.push_back(state);
}

void Game::pop_state(unsigned numStates) {
	for (unsigned i = 0; i < numStates; i++) {
		delete states.back();
		states.pop_back();
	}
	clickTimer = 0;
}

void Game::backToMainState() {
	pop_state(states.size() - 1);
}

void Game::game_loop() {
	sf::Clock clock;
	float dt = 0.0f;

	while (window.isOpen()) {
		// Time Manipuation
		sf::Time elapsed = clock.restart();
		dt = elapsed.asSeconds();

		// RNG Mainpulation
		rng = elapsed.asMicroseconds();
		rng *= rng;
		rng *= (rng / 100); // about 17 digits
		rng = abs(rng);

		// Exception handling
		if (!current_state()) {
			continue;
		}
		else {
			current_state()->handle_input();
			current_state()->update(dt);

			current_state()->draw();
			window.display();
		}
	}
}

void Game::setup() {
	// Create a View
	view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	//Setting up Sound
	std::vector<std::string> soundFiles{ RESOURCE_PATH + "Audio/PlayState.ogg", RESOURCE_PATH + "Audio/Bells_Cut.wav",
										  RESOURCE_PATH + "Audio/Coin_Collect.wav", RESOURCE_PATH + "Audio/EventStates.ogg",
										  RESOURCE_PATH + "Audio/GameOver.wav", RESOURCE_PATH + "Audio/	MainMenu.ogg",
										  RESOURCE_PATH + "Audio/Ship_Explosion.wav" , RESOURCE_PATH + "Audio/Store.ogg",
										  RESOURCE_PATH + "Audio/Tutorial.ogg",
										  RESOURCE_PATH + "Audio/WarZone2.wav", RESOURCE_PATH + "Audio/Tornado.wav",
										  RESOURCE_PATH + "Audio/ButtonClick.wav" };

	soundList = Sound_(soundFiles);
	soundList.setLoop(RESOURCE_PATH + "Audio/PlayState.ogg");
	soundList.setLoop(RESOURCE_PATH + "Audio/EventStates.ogg");
	soundList.setLoop(RESOURCE_PATH + "Audio/Store.ogg");

	try {
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

		defaultPlayer = Player(playerTexture, sf::Vector2u(9, 9), sf::Vector2f(VIEW_WIDTH / 2, 0.0), 8, 5, 0);
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
		makeTexture(backgroundTexture[6], "Background/astsuccess2.png");
		makeTexture(backgroundTexture[7], "Background/lastsuccess.jpg");
		makeTexture(backgroundTexture[8], "Background/veersuccess.jpg");
		makeTexture(backgroundTexture[9], "Background/veerfail.jpg");
		makeTexture(backgroundTexture[10], "Background/veersuccess2.jpg");
		makeTexture(backgroundTexture[11], "Background/astfail.jpg");
		makeTexture(backgroundTexture[12], "Background/Whirlwind.jpg");
		makeTexture(backgroundTexture[13], "Background/SuckFail.jpg");
		makeTexture(backgroundTexture[14], "Background/SuckSuccess.jpg");

		// Create Fonts
		makeFont(font[0], "Font/Mont-Heavy.otf");
		makeFont(font[1], "Font/Doctor-Glitch.otf");
		makeFont(font[2], "Font/Glitch-City.ttf");
		makeFont(font[3], "Font/Roboto-Italic.ttf");
		makeFont(font[4], "Font/Roboto-Black.ttf");

	}
	catch (const std::string& error) {
		std::cerr << "\n\n" << error << " failed to load\nSee if the file is missing or mispelled\n\n";
		exit(1);
	}
}

void Game::makeCollisionTexture(sf::Texture& text, std::string file) {
	if (!Collision::CreateTextureAndBitmask(text, RESOURCE_PATH + file))
		throw file;
}

void Game::makeTexture(sf::Texture& text, std::string file) {
	if (!text.loadFromFile(RESOURCE_PATH + file))
		throw file;
}

void Game::makeFont(sf::Font& font, std::string file) {
	if (!font.loadFromFile(RESOURCE_PATH + file))
		throw file;
}





