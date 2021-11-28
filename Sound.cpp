
#include "Sound.h"

Sound::~Sound() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Sound::Load(const char* filename) {
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
}

void Sound::Play() {
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}

void Sound::Stop() {
    SDL_PauseAudioDevice(deviceId, 1);
}
