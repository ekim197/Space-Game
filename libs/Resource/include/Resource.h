#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
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
    extern sf::Texture backgroundTexture[20];
    extern sf::Font font[5];

    // Sound
    extern Sound_ soundList;

    // Time stuff
    extern long long int rng;
    extern float clickTimer;

    // File names
    extern std::string highScoreFile;

    // View
    extern const float VIEW_WIDTH;
    extern const float VIEW_HEIGHT;
    extern const float VIEW_RATIO;

    // File
    extern const std::string RESOURCE_PATH;

    // Functions
    void makeCollisionTexture(sf::Texture& text, std::string file);
    void makeTexture(sf::Texture& text, std::string file);
    void makeFont(sf::Font& font, std::string file);
}

#endif // RESOURCE_H

