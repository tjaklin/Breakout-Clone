#pragma once

#include <SDL2/SDL.h>
#include <string>

class Sound {
public:
	Sound(std::string filePath);
	~Sound();

	void play();
private:
	SDL_AudioDeviceID audioDevice_m;
	SDL_AudioSpec wavSpec_m;
	Uint32 wavLength_m;
	Uint8* wavBuffer_m;
};
