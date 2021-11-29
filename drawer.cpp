
#include <iostream>
#include <cstring>
#include "drawer.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


drawer::drawer(SDL_Window *gWindow, SDL_Renderer *gRenderer) {
    gWindow_ = gWindow;
    gRenderer_ = gRenderer;
}

void drawer::initWindow() {
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    gWindow_ = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer_ = SDL_CreateRenderer(gWindow_, -1, SDL_RENDERER_ACCELERATED);
}

void drawer::getImage(std::string const path) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedImgSurface = IMG_Load(path.c_str());
    if (loadedImgSurface == nullptr) std::cout << "Error loading Surface\n";
    newTexture = SDL_CreateTextureFromSurface(gRenderer_, loadedImgSurface);
    SDL_FreeSurface(loadedImgSurface);
    SDL_RenderClear(gRenderer_);
    SDL_RenderCopy(gRenderer_, newTexture, nullptr, nullptr);
    SDL_RenderPresent(gRenderer_);
}

void drawer::getButton(std::string const path, int x, int y, int w, int h) {
    SDL_Texture *NewTexture = nullptr;
    SDL_Surface *loadedImgSurface = IMG_Load(path.c_str());
    NewTexture = SDL_CreateTextureFromSurface(gRenderer_, loadedImgSurface);
    SDL_Rect viewPort;
    viewPort.x = x;
    viewPort.y = y;
    viewPort.w = w;
    viewPort.h = h;
    SDL_RenderSetViewport(gRenderer_, &viewPort);
    SDL_RenderCopy(gRenderer_, NewTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer_);
    SDL_FreeSurface(loadedImgSurface);
}

void drawer::printEquation(std::string const eq) {
    TTF_Font *font = TTF_OpenFont("DoctorSoos.ttf", 84);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                eq.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer_,
                                                        surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {65, 250, texW, texH};
    SDL_RenderCopy(gRenderer_, texture, NULL, &dstrect);
    SDL_RenderPresent(gRenderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void drawer::printScore(std::string const point) {
    TTF_Font *font = TTF_OpenFont("DoctorSoos.ttf", 48);
    SDL_Color color = {141, 136, 117};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                point.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer_,
                                                        surface);
    const int scoreX = 165;
    const int scoreY = 85;
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    //SDL_SetTextureAlphaMod(texture, 1);
    SDL_Rect dstrect = {scoreX, scoreY, texW, texH};
    //SDL_SetTextureAlphaMod(texture, 1);
    SDL_RenderCopy(gRenderer_, texture, NULL, &dstrect);
    SDL_RenderPresent(gRenderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void drawer::clearRender() {
    SDL_Rect resetViewPort;
    resetViewPort.x = 0;
    resetViewPort.y = 0;
    resetViewPort.w = 400;
    resetViewPort.h = 10;
    SDL_RenderSetViewport(gRenderer_, &resetViewPort);
}

void drawer::resetAfterARound() {
    SDL_RenderClear(gRenderer_);
    SDL_DestroyRenderer(gRenderer_);
    gRenderer_ = SDL_CreateRenderer(gWindow_, -1, SDL_RENDERER_ACCELERATED);
}

