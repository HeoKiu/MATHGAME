
#include "../include/Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <vector>


Drawer::Drawer(SDL_Window *window, SDL_Renderer *renderer) {
    window_ = window;
    renderer_ = renderer;
}

void Drawer::InitWindow() {
    const std::vector<int> mix_audio{44100, 2, 2048};
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(mix_audio[0], MIX_DEFAULT_FORMAT, mix_audio[1], mix_audio[2]);
    window_ = SDL_CreateWindow(kGameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

void Drawer::GetImage(std::string const path) {
    SDL_Texture *new_texture;
    SDL_Surface *loaded_img_surface = IMG_Load(path.c_str());
    new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_img_surface);
    SDL_FreeSurface(loaded_img_surface);
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, new_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
}

void Drawer::GetButton(std::string const path, size_t x_coordinate, size_t y_coordinate, size_t w_coordinate, size_t h_coordinate) {
    SDL_Texture *new_texture;
    SDL_Surface *loaded_img_surface = IMG_Load(path.c_str());
    new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_img_surface);
    SDL_Rect view_port;
    view_port.x = x_coordinate;
    view_port.y = y_coordinate;
    view_port.w = w_coordinate;
    view_port.h = h_coordinate;
    SDL_RenderSetViewport(renderer_, &view_port);
    SDL_RenderCopy(renderer_, new_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
    SDL_FreeSurface(loaded_img_surface);
}

void Drawer::PrintEquation(std::string const eq) {
    const size_t font_size = 84;
    const size_t font_color = 255;
    const int tex_x = 65;
    const int tex_y = 250;
    int tex_w = 0;
    int tex_h = 0;
    TTF_Font *font = TTF_OpenFont("../asset/fonts/DoctorSoos.ttf", font_size);
    SDL_Color color = {font_color, font_color, font_color};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                eq.c_str(), color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_,surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect rect = {tex_x, tex_y, tex_w, tex_h};
    SDL_RenderCopy(renderer_, texture, nullptr, &rect);
    SDL_RenderPresent(renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::PrintScore(std::string point) {
    const size_t font_size = 48;
    std::vector<Uint8> font_color{141, 136, 117};
    TTF_Font *font = TTF_OpenFont("../asset/fonts/DoctorSoos.ttf", font_size);

    SDL_Color color = {font_color[0], font_color[1], font_color[2]};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                point.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_,
                                                        surface);
    const int score_x = 165;
    const int score_y = 85;
    int tex_w = 0;
    int tex_h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect rect = {score_x, score_y, tex_w, tex_h};
    SDL_RenderCopy(renderer_, texture, nullptr, &rect);
    SDL_RenderPresent(renderer_);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Drawer::ClearRender() {
    std::vector<size_t> view_port{0,0,400,100};
    SDL_Rect reset_view_port;
    reset_view_port.x = view_port[0];
    reset_view_port.y = view_port[1];
    reset_view_port.w = view_port[2];
    reset_view_port.h = view_port[3];
    SDL_RenderSetViewport(renderer_, &reset_view_port);
}

void Drawer::ResetAfterARound() {
    SDL_RenderClear(renderer_);
    SDL_DestroyRenderer(renderer_);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}
std::string Drawer::GetPointString(int point) {
    std::string final_string;
    std::stringstream ss;
    ss << point;
    final_string = ss.str();
    return final_string;
}
