
#include "../include/Music.h"

Music::~Music() {
    SDL_CloseAudioDevice(audioDeviceId);
    SDL_FreeWAV(audioBuf);
}

void Music::Load(const char* filename) {
    SDL_LoadWAV(filename, &wavSpec, &audioBuf, &wavLength);
    audioDeviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
}

void Music::Play() {
    SDL_QueueAudio(audioDeviceId, audioBuf, wavLength);
    SDL_PauseAudioDevice(audioDeviceId, 0);
}

void Music::Stop() {
    SDL_PauseAudioDevice(audioDeviceId, 1);
    SDL_CloseAudioDevice(audioDeviceId);
}

