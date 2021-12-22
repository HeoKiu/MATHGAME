
#include "../include//Music.h"
#include "../include/Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
class Game {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Music open_music;
    Music over_music;
    Music defuse_music;
    Music in_game_music;

    Drawer game_print(window, renderer);

public:
    std::string GetStringEquation(MathEquation equation);

    void PrintEq(MathEquation eq);

    void Intro();

    bool KeyPressed(MathEquation eq);

    std::string GetPointString(int point);

    bool TimeDiscounting(MathEquation eq);

    void StartARound(int point);

    void PrintMenu();

    void GameOver(int point);
};
