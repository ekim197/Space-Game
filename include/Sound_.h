#ifndef SOUND__H
#define SOUND__H

#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>

class Sound_{
private:
	static std::string getFileType(std::string s);
	static bool isFileTypeWav(std::string s);

public:
	// Public Variables
	static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	static std::vector<std::string> listOfSoundFiles;
	static sf::Sound sound_player;
	static sf::Music music_player;
	static std::string currentMusicPlaying;

	// Constructors and Destructors
	Sound_() = default;
	Sound_(std::vector<std::string> s);
	Sound_(const Sound_&);
	Sound_& operator=(const Sound_& other);
    ~Sound_() = default;

    // Action
	static void addSound(std::string s);
	static void playSound(std::string s);
	static void playSound(std::string s, float volume);
	static void playSound(std::string s, float volume, float pitch);
	static void setLoop(std::string s);
	static void turnOffLoop(std::string s);
	static void pauseSound(std::string s);
	static void stopSound(std::string s);
	static void playOffset(std::string s, float seconds);
    static void stopAllSounds();
	static void resetPitchVolume();
	static bool getStatusOfMusic(std::string soundName);
};

#endif // SOUND__H
