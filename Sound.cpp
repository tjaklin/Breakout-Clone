#include "Sound.hpp"

Sound::Sound(std::string filePath) {
    SDL_LoadWAV(filePath.c_str(), &wavSpec_m, &wavBuffer_m, &wavLength_m);
    audioDevice_m = SDL_OpenAudioDevice(NULL, 0, &wavSpec_m, NULL, 0);
}
Sound::~Sound() {
    SDL_CloseAudioDevice(audioDevice_m);
    SDL_FreeWAV(wavBuffer_m);
}

void Sound::play() {
    SDL_QueueAudio(audioDevice_m, wavBuffer_m, wavLength_m);
    SDL_PauseAudioDevice(audioDevice_m, 0);
}
