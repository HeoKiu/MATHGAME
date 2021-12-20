
#include "../include/Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>
#include <vector>


Drawer::Drawer(SDL_Window *window, SDL_Renderer *renderer) {
    Window_ = window;
    Renderer_ = renderer;
}

void Drawer::initWindow() {
    const std::vector<int> mix_audio{44100, 2, 2048};
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(mix_audio[0], MIX_DEFAULT_FORMAT, mix_audio[1], mix_audio[2]);
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
    const size_t font_size = 84;
    const size_t font_color = 255;
    const int tex_x = 65;
    const int tex_y = 250;
    int tex_w = 0;
    int tex_h = 0;
    TTF_Font *font = TTF_OpenFont("../fonts/DoctorSoos.ttf", font_size);
    SDL_Color color = {font_color, font_color, font_color};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                eq.c_str(), color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer_,surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect rect = {tex_x, tex_y, tex_w, tex_h};
    SDL_RenderCopy(Renderer_, texture, nullptr, &rect);
    SDL_RenderPresent(Renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::printScore(std::string point) {
    const size_t font_size = 48;
    std::vector<Uint8> font_color{141, 136, 117};
    TTF_Font *font = TTF_OpenFont("../fonts/DoctorSoos.ttf", font_size);

    SDL_Color color = {font_color[0], font_color[1], font_color[2]};
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
    std::vector<size_t> view_port{0,0,400,100};
    SDL_Rect reset_view_port;
    reset_view_port.x = view_port[0];
    reset_view_port.y = view_port[1];
    reset_view_port.w = view_port[2];
    reset_view_port.h = view_port[3];
    SDL_RenderSetViewport(Renderer_, &reset_view_port);
}

void Drawer::resetAfterARound() {
    SDL_RenderClear(Renderer_);
    SDL_DestroyRenderer(Renderer_);
    Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
}
