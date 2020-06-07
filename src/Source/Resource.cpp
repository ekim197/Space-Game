#include "Resource.h"

namespace Resource{
// Textures, Buffers, and Fonts
    sf::SoundBuffer bufferTEMP;
    sf::Texture playerTexture[9];
    sf::Texture asteroidTexture;
    sf::Texture planetTexture;
    sf::Texture coinTexture;
    sf::Texture backgroundTexture[6];
    sf::Font font[5];
    // Sound
    sf::Sound sound;
    sf::Music music[2];
    // Time stuff
    long long int rng = 0;
}
