#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "Sound_.h"

Sound_::Sound_() {}
Sound_::Sound_(std::vector<std::string> s) {
	//Using overloaded assignment operator in vector
	listOfSoundFiles = s;

	for (size_t i = 0; i < listOfSoundFiles.size(); i++) {
		if (isFileTypeWav) {
			sf::SoundBuffer buffer;

			if (!buffer.loadFromFile(listOfSoundFiles[i])) {
				//Have a catch/throw
				std::cout << "Error in loading sound";
			}

			soundBuffers[listOfSoundFiles[i]] = buffer;
		}
	}
}

Sound_::Sound_(const Sound_& s) {
	//Using = overloaded operator
	this->soundBuffers = s.soundBuffers;
	this->listOfSoundFiles = s.listOfSoundFiles;

}
Sound_::~Sound_() {}

void Sound_::addSound(std::string s) {
	//Add to list of sounds
	listOfSoundFiles.push_back(s);
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(s)) {
		//Have a catch/throw
		std::cout << "Error in loading sound";
	}

	//Add to sound buffers
	soundBuffers[s] = buffer;
}

void Sound_::playSound(std::string s) {
	if (isFileTypeWav) {
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.play();
	}
	else {
		if (music_player.openFromFile(s)) {
			//Throw error
			std::cout << "Can't play music";
		}

		music_player.play();
	}
}

//Max volume is 100
void Sound_::playSound(std::string s, float volume) {
	if (isFileTypeWav) {
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.setVolume(volume);
		sound_player.play();
	}
	else {
		if (music_player.openFromFile(s)) {
			//Throw error
			std::cout << "Can't play music";
		}

		music_player.setVolume(volume);
		music_player.play();
	}
}

//Pitch at 1 is unchanged, greater means higher pitch
void Sound_::playSound(std::string s, float volume, float pitch) {
	if (isFileTypeWav) {
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.setVolume(volume);
		sound_player.setPitch(pitch);
		sound_player.play();
	}
	else {
		if (music_player.openFromFile(s)) {
			//Throw error
			std::cout << "Can't play music";
		}
		music_player.setVolume(volume);
		music_player.setPitch(pitch);
		music_player.play();
	}
}

void Sound_::setLoop() {
	if (isFileTypeWav) {
		sound_player.setLoop(true);
	}
	else {
		music_player.setLoop(true);
	}
}

void Sound_::turnOffLoop() {
	if (isFileTypeWav) {
		sound_player.setLoop(false);
	}
	else {
		music_player.setLoop(false);
	}
}

void Sound_::pauseSound() {
	if (isFileTypeWav) {
		sound_player.pause();
	}
	else {
		music_player.pause();
	}
}

void Sound_::stopSound() {
	if (isFileTypeWav) {
		sound_player.stop();
	}
	else {
		music_player.stop();
	}
}

void Sound_::playOffset(float seconds) {
	if (isFileTypeWav) {
		sound_player.setPlayingOffset(sf::seconds(seconds));
	}
	else {
		music_player.setPlayingOffset(sf::seconds(seconds));
	}
}

Sound_& Sound_::operator=(const Sound_& other) {
	this->soundBuffers = other.soundBuffers;
	this->listOfSoundFiles = other.listOfSoundFiles;
	return *this;
}

std::string Sound_::getFileType(std::string s) {
	std::string fileType = s.substr(s.length() - 3, 3);
	return fileType;
}

bool Sound_::isFileTypeWav(std::string s) {
	if (getFileType(s).compare("wav") == 0) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_map<std::string, sf::SoundBuffer> Sound_::soundBuffers{};
std::vector<std::string> Sound_::listOfSoundFiles{};
sf::Sound Sound_::sound_player{};
sf::Music Sound_::music_player{};
