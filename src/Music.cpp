
#include "../include/Music.h"

Music::~Music() {
    SDL_CloseAudioDevice(audio_device_id_);
    SDL_FreeWAV(audio_buf_);
}

void Music::Load(const char* filename) {
    SDL_LoadWAV(filename, &wav_spec_, &audio_buf_, &wav_length_);
    audio_device_id_ = SDL_OpenAudioDevice(nullptr, 0, &wav_spec_, nullptr, 0);
}

void Music::Play() {
    SDL_QueueAudio(audio_device_id_, audio_buf_, wav_length_);
    SDL_PauseAudioDevice(audio_device_id_, 0);
}

void Music::Stop() {
    SDL_PauseAudioDevice(audio_device_id_, 1);
    SDL_CloseAudioDevice(audio_device_id_);
}

