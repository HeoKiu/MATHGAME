
#ifndef GAMESDL_DRAWER_H
#define GAMESDL_DRAWER_H
#include "MathEquation.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>


const int kScreenWidth = 400;
const int kScreenHeight = 600;
const std::string kGameName = "Quick Maths";


class Drawer {
private:
    Drawer();
    SDL_Window* window_;
    SDL_Renderer* renderer_;
public:
    ~Drawer() = default;
    Drawer(SDL_Window* window, SDL_Renderer* renderer);
    void InitWindow();
    void GetImage(std::string const path);
    void GetButton(std::string const path, size_t x_coordinate, size_t y_coordinate, size_t w_coordinate, size_t h_coordinate);
    void PrintEquation(std::string const eq);
    void DrawTimeLeft(int beginning_width);
    void PrintScore(std::string const point);
    void ClearRender();
    void ResetAfterARound();
    std::string GetPointString(int point);

};

#endif//GAMESDL_DRAWER_H
