
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
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *audioBuf;
    SDL_AudioDeviceID audioDeviceId;
};


#endif//GAMESDL_MUSIC_H
