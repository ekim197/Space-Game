#include "Resource.h"

namespace Resource{
// Textures, Buffers, and Fonts
    sf::SoundBuffer bufferTEMP;
    sf::Texture playerTexture[9];
    sf::Texture asteroidTexture;
    sf::Texture planetTexture;
    sf::Texture coinTexture;
    sf::Texture warZoneTexture;
    sf::Texture backgroundTexture[20];
    sf::Font font[5];
    // Sound
	Sound_ soundList;
    // Time stuff
    long long int rng = 0;
    float clickTimer = 0;
    std::string highScoreFile = "High_Score.bin";

    // Other
    const float VIEW_WIDTH = 1600.0;
    const float VIEW_HEIGHT = 900.0;
    const float VIEW_RATIO = VIEW_HEIGHT / 900.0;
    const std::string RESOURCE_PATH = "resources/";

}
