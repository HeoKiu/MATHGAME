
#include "Sound.h"

Sound::~Sound() {
    SDL_CloseAudioDevice(audioDeviceId);
    SDL_FreeWAV(audioBuf);
}

void Sound::Load(const char* filename) {
    SDL_LoadWAV(filename, &wavSpec, &audioBuf, &wavLength);
    audioDeviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
}

void Sound::Play() {
    SDL_QueueAudio(audioDeviceId, audioBuf, wavLength);
    SDL_PauseAudioDevice(audioDeviceId, 0);
}

void Sound::Stop() {
    SDL_PauseAudioDevice(audioDeviceId, 1);
}
