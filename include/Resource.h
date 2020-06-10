#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include "Entity.h"
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Collision.h"
#include "Sound_.h"

namespace Resource{
    // Textures, Buffers, and Fonts
    extern sf::SoundBuffer bufferTEMP;
    extern sf::Texture playerTexture[9];
    extern sf::Texture asteroidTexture;
    extern sf::Texture planetTexture;
    extern sf::Texture coinTexture;
    extern sf::Texture warZoneTexture;
    extern sf::Texture backgroundTexture[12];
    extern sf::Font font[5];
    // Sound
    extern Sound_ soundList;
    // Time stuff
    extern long long int rng;
    extern float clickTimer;
    // File names
    extern std::string highScoreFile;

}


#endif // RESOURCE_H

