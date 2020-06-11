#include "Sound_.h"
#include <cstdlib>

std::unordered_map<std::string, sf::SoundBuffer> Sound_::soundBuffers{};
std::vector<std::string> Sound_::listOfSoundFiles{};
sf::Sound Sound_::sound_player{};
sf::Sound Sound_::sound_player2{};
sf::Music Sound_::music_player{};
std::string Sound_::currentMusicPlaying{};

Sound_::Sound_(std::vector<std::string> s) {
	// Using overloaded assignment operator in vector
	listOfSoundFiles = s;

	for (size_t i = 0; i < listOfSoundFiles.size(); i++) {
		if (isFileTypeWav(s[i])) {
			sf::SoundBuffer buffer;

			if (!buffer.loadFromFile(listOfSoundFiles[i])) {
				// Have a catch/throw
				std::cerr << "Error in loading sound";
				exit(6);
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

Sound_& Sound_::operator=(const Sound_& other) {
	this->soundBuffers = other.soundBuffers;
	this->listOfSoundFiles = other.listOfSoundFiles;
	return *this;
}

void Sound_::addSound(std::string s) {
	//Add to list of sounds
	listOfSoundFiles.push_back(s);
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(s)) {
		//Have a catch/throw
		std::cerr << "Error in loading sound";
	}

	//Add to sound buffers
	soundBuffers[s] = buffer;
}

void Sound_::playSound(std::string s) {
	if (isFileTypeWav(s)) {
        resetPitchVolume();
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.play();
	}
	else {
        resetPitchVolume();
		music_player.openFromFile(s);
		music_player.play();
		currentMusicPlaying = s;
	}
}

//Max volume is 100
void Sound_::playSound(std::string s, float volume) {
	if (isFileTypeWav(s)) {
        resetPitchVolume();
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.setVolume(volume);
		sound_player.play();
	}
	else {
		resetPitchVolume();
		music_player.openFromFile(s);
		music_player.setVolume(volume);
		music_player.play();
		currentMusicPlaying = s;
	}
}

//Pitch at 1 is unchanged, greater means higher pitch
void Sound_::playSound(std::string s, float volume, float pitch) {
	if (isFileTypeWav(s)) {
        resetPitchVolume();
		sound_player.setBuffer(soundBuffers[s]);
		sound_player.setVolume(volume);
		sound_player.setPitch(pitch);
		sound_player.play();
	}
	else {
		resetPitchVolume();
        music_player.openFromFile(s);
		music_player.setVolume(volume);
		music_player.setPitch(pitch);
		music_player.play();
		currentMusicPlaying = s;
	}
}

void Sound_::setLoop(std::string s) {
	if (isFileTypeWav(s))
		sound_player.setLoop(true);
	else
		music_player.setLoop(true);
}

void Sound_::turnOffLoop(std::string s) {
	if (isFileTypeWav(s))
		sound_player.setLoop(false);
	else
		music_player.setLoop(false);
}

void Sound_::pauseSound(std::string s) {
	if (isFileTypeWav(s))
		sound_player.pause();
	else
		music_player.pause();
}

void Sound_::stopSound(std::string s) {
	if (isFileTypeWav(s))
		sound_player.stop();
	else
		music_player.stop();
}

void Sound_::playOffset(std::string s, float seconds) {
	if (isFileTypeWav(s))
		sound_player.setPlayingOffset(sf::seconds(seconds));
	else
		music_player.setPlayingOffset(sf::seconds(seconds));
}

std::string Sound_::getFileType(std::string s) {
	std::string fileType = s.substr(s.length() - 3, 3);
	return fileType;
}

bool Sound_::isFileTypeWav(std::string s) {
	std::size_t found = s.find(".wav");
	if (found != std::string::npos)
		return true;
	else
		return false;
}

void Sound_::stopAllSounds() {
	sound_player.stop();
	music_player.stop();
	currentMusicPlaying = "";
}

void Sound_::resetPitchVolume() {
	sound_player.setVolume(100);
	sound_player.setPitch(1);
	sound_player2.setVolume(100);
	sound_player2.setPitch(1);
	music_player.setVolume(100);
	music_player.setPitch(1);
}

bool Sound_::getStatusOfMusic(std::string soundName) {
	if (currentMusicPlaying == soundName) {
		return true;
	}
	else {
		return false;
	}
}

void Sound_::playSoundConcurrently(std::string soundName, float volume) {
	if (isFileTypeWav(soundName)) {
		resetPitchVolume();
		sound_player2.setBuffer(soundBuffers[soundName]);
		sound_player2.setVolume(volume);
		sound_player2.play();
	}
}

int Sound_::RecordSoundAndGetAmplitude(int milliseconds) {

	if (!sf::SoundBufferRecorder::isAvailable())
	{
		std::cout << "No Sound Recorders available";

	}

	// create the recorder
	sf::SoundBufferRecorder recorder;

	// start the capture
	recorder.start();

	// start the clock
	sf::Clock clock; 

	while (clock.getElapsedTime().asMilliseconds() != milliseconds) {}
	recorder.stop();

	// retrieve the buffer that contains the captured audio data
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	const sf::Int16* samples = buffer.getSamples();

	int largestAmplitude = 0;
	int boundary1 = 2000;
	int boundary2 = 10000;

	for (auto i = 0; i < 2000; i++)
	{
		int difference = abs(samples[i] - samples[i + 1]);
		std::cout << samples[i] << std::endl;

		if (difference < boundary1 && abs(samples[i]) <= boundary2) {
			if (largestAmplitude < abs(samples[i])) {
				largestAmplitude = abs(samples[i]);
			}
		}
	}

	return largestAmplitude;
}
