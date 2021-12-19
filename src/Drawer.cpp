
#include "../include/Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>


Drawer::Drawer(SDL_Window *window, SDL_Renderer *renderer) {
    Window_ = window;
    Renderer_ = renderer;
}

void Drawer::initWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Window_ = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
}

void Drawer::getImage(std::string const path) {
    SDL_Texture *new_texture;
    SDL_Surface *loaded_img_surface = IMG_Load(path.c_str());
    new_texture = SDL_CreateTextureFromSurface(Renderer_, loaded_img_surface);
    SDL_FreeSurface(loaded_img_surface);
    SDL_RenderClear(Renderer_);
    SDL_RenderCopy(Renderer_, new_texture, nullptr, nullptr);
    SDL_RenderPresent(Renderer_);
}

void Drawer::getButton(std::string const path, size_t x_coordinate, size_t y_coordinate, size_t w_coordinate, size_t h_coordinate) {
    SDL_Texture *new_texture;
    SDL_Surface *loaded_img_surface = IMG_Load(path.c_str());
    new_texture = SDL_CreateTextureFromSurface(Renderer_, loaded_img_surface);
    SDL_Rect view_port;
    view_port.x = x_coordinate;
    view_port.y = y_coordinate;
    view_port.w = w_coordinate;
    view_port.h = h_coordinate;
    SDL_RenderSetViewport(Renderer_, &view_port);
    SDL_RenderCopy(Renderer_, new_texture, nullptr, nullptr);
    SDL_RenderPresent(Renderer_);
    SDL_FreeSurface(loaded_img_surface);
}

void Drawer::printEquation(std::string const eq) {
    TTF_Font *font = TTF_OpenFont("../fonts/DoctorSoos.ttf", 84);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                eq.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer_,
                                                        surface);
    int tex_w = 0;
    int tex_h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect rect = {65, 250, tex_w, tex_h};
    SDL_RenderCopy(Renderer_, texture, nullptr, &rect);
    SDL_RenderPresent(Renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::printScore(std::string point) {
    TTF_Font *font = TTF_OpenFont("../fonts/DoctorSoos.ttf", 48);
    SDL_Color color = {141, 136, 117};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                point.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer_,
                                                        surface);
    const int score_x = 165;
    const int score_y = 85;
    int tex_w = 0;
    int tex_h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect rect = {score_x, score_y, tex_w, tex_h};
    SDL_RenderCopy(Renderer_, texture, nullptr, &rect);
    SDL_RenderPresent(Renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::clearRender() {
    SDL_Rect reset_view_port;
    reset_view_port.x = 0;
    reset_view_port.y = 0;
    reset_view_port.w = 400;
    reset_view_port.h = 10;
    SDL_RenderSetViewport(Renderer_, &reset_view_port);
}

void Drawer::resetAfterARound() {
    SDL_RenderClear(Renderer_);
    SDL_DestroyRenderer(Renderer_);
    Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
}

