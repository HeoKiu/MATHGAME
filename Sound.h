
#ifndef GAMESDL_SOUND_H
#define GAMESDL_SOUND_H

#include <SDL2/SDL.h>

class Sound {
public:
    ~Sound();
    void Load(const char* filename);
    void Play();
    void Stop();
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
};


#endif//GAMESDL_SOUND_H
