
#include "Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>


Drawer::Drawer(SDL_Window *Window, SDL_Renderer *Renderer) {
    Window_ = Window;
    Renderer_ = Renderer;
}

void Drawer::initWindow() {
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Window_ = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
}

void Drawer::getImage(std::string const path) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedImgSurface = IMG_Load(path.c_str());
    if (loadedImgSurface == nullptr) std::cout << "Error loading Surface\n";
    newTexture = SDL_CreateTextureFromSurface(Renderer_, loadedImgSurface);
    SDL_FreeSurface(loadedImgSurface);
    SDL_RenderClear(Renderer_);
    SDL_RenderCopy(Renderer_, newTexture, nullptr, nullptr);
    SDL_RenderPresent(Renderer_);
}

void Drawer::getButton(std::string const path, int x, int y, int w, int h) {
    SDL_Texture *NewTexture = nullptr;
    SDL_Surface *loadedImgSurface = IMG_Load(path.c_str());
    NewTexture = SDL_CreateTextureFromSurface(Renderer_, loadedImgSurface);
    SDL_Rect viewPort;
    viewPort.x = x;
    viewPort.y = y;
    viewPort.w = w;
    viewPort.h = h;
    SDL_RenderSetViewport(Renderer_, &viewPort);
    SDL_RenderCopy(Renderer_, NewTexture, NULL, NULL);
    SDL_RenderPresent(Renderer_);
    SDL_FreeSurface(loadedImgSurface);
}

void Drawer::printEquation(std::string const eq) {
    TTF_Font *font = TTF_OpenFont("DoctorSoos.ttf", 84);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                eq.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer_,
                                                        surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {65, 250, texW, texH};
    SDL_RenderCopy(Renderer_, texture, NULL, &dstrect);
    SDL_RenderPresent(Renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::printScore(std::string const point) {
    TTF_Font *font = TTF_OpenFont("DoctorSoos.ttf", 48);
    SDL_Color color = {141, 136, 117};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                point.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer_,
                                                        surface);
    const int scoreX = 165;
    const int scoreY = 85;
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    //SDL_SetTextureAlphaMod(texture, 1);
    SDL_Rect dstrect = {scoreX, scoreY, texW, texH};
    //SDL_SetTextureAlphaMod(texture, 1);
    SDL_RenderCopy(Renderer_, texture, NULL, &dstrect);
    SDL_RenderPresent(Renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::clearRender() {
    SDL_Rect resetViewPort;
    resetViewPort.x = 0;
    resetViewPort.y = 0;
    resetViewPort.w = 400;
    resetViewPort.h = 10;
    SDL_RenderSetViewport(Renderer_, &resetViewPort);
}

void Drawer::resetAfterARound() {
    SDL_RenderClear(Renderer_);
    SDL_DestroyRenderer(Renderer_);
    Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
}

