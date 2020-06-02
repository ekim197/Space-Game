#pragma once
#include <SFML/Audio.hpp>
#include <iostream> 
#include <unordered_map> 
#include <string>
#include <vector>

class Sound_ {
private:
	static std::string getFileType(std::string s);
	static bool isFileTypeWav(std::string s);
public:
	static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	static std::vector<std::string> listOfSoundFiles;
	static sf::Sound sound_player;
	static sf::Music music_player;

	Sound_();	
	Sound_(std::vector<std::string> s);
	Sound_(const Sound_&);
	static void addSound(std::string s);
	static void playSound(std::string s);
	static void playSound(std::string s, float volume);
	static void playSound(std::string s, float volume, float pitch);
	static void setLoop();
	static void turnOffLoop();
	static void pauseSound();
	static void stopSound();
	static void playOffset(float seconds);
	Sound_& operator=(const Sound_& other);
	~Sound_();
};


