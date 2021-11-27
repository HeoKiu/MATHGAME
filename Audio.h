//
// Created by duc on 27.11.2021.
//

#ifndef GAMESDL_AUDIO_H
#define GAMESDL_AUDIO_H

#include <SDL2/SDL.h>

class Audio {
public:
    ~Audio();
    void load(const char* filename);
    void play();
    void stop();
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
};


#endif//GAMESDL_AUDIO_H
