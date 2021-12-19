
#ifndef GAMESDL_MUSIC_H
#define GAMESDL_MUSIC_H

#include <SDL2/SDL.h>

class Music {
public:
    ~Music();
    void Load(const char* filename);
    void Play();
    void Stop();
private:
    SDL_AudioSpec wav_spec_;
    Uint32 wav_length_;
    Uint8 *audio_buf_;
    SDL_AudioDeviceID audio_device_id_;
};


#endif//GAMESDL_MUSIC_H
