#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
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
    extern sf::Texture backgroundTexture[6];
    extern sf::Font font[5];
    // Sound
    extern sf::Sound sound;
    extern sf::Music music[2];
    // Time stuff
    extern long long int rng;
}


#endif // RESOURCE_H

