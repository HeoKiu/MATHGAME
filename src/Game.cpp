#include "../include//Music.h"
#include "../include/Drawer.h"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

SDL_Window *window;
SDL_Renderer *renderer;
Drawer game_print(window, renderer);
Music open_music;
Music over_music;
Music defuse_music;
Music in_game_music;

std::string GetStringEquation(MathEquation equation) {
    std::string final_string;
    std::stringstream second_value;
    std::stringstream first_value;
    std::stringstream third_value;
    first_value << equation.firstNumber;
    final_string = first_value.str();
    second_value << equation.secondNumber;
    final_string = final_string + " + " + second_value.str();
    third_value << equation.thirdNumber;
    final_string = final_string + " = " + third_value.str();
    return final_string;
}

void PrintEq(MathEquation eq) {
    const size_t delay_time = 500;
    const std::vector<int> wrong_button{30, 400, 165, 145};
    const std::vector<int> right_button{210, 400, 165, 145};
    in_game_music.Load("../sounds/game.wav");
    game_print.getImage("../images/defusing.png");
    in_game_music.Play();
    SDL_Delay(delay_time);
    game_print.printEquation(GetStringEquation(eq));
    game_print.getButton("../images/wrong.png", wrong_button[0], wrong_button[1], wrong_button[2], wrong_button[3]);
    game_print.getButton("../images/right.png", right_button[0], right_button[1], right_button[2], right_button[3]);
    game_print.clearRender();
    in_game_music.Stop();
}

void Intro() {
    int number_images = 8;
    game_print.initWindow();
    const std::vector<int> delay_time{100, 500, 250, 1600, 1300};
    open_music.Load("../sounds/planting.wav");
    defuse_music.Load("../sounds/defusing.wav");
    open_music.Play();
    while (number_images-- > 0) {
        game_print.getImage("../images/introScene1.png");
        SDL_Delay(delay_time[0]);
        game_print.getImage("../images/introScene2.png");
        SDL_Delay(delay_time[0]);
    }
    game_print.getImage("../images/introScene3.png");
    SDL_Delay(delay_time[1]);
    game_print.getImage("../images/introScene4.png");
    SDL_Delay(delay_time[2]);
    game_print.getImage("../images/introScene5.png");
    SDL_Delay(delay_time[3]);
    defuse_music.Play();
    game_print.getImage("../images/defusing.png");
    SDL_Delay(delay_time[4]);
    defuse_music.Stop();
    open_music.Stop();
    SDL_RenderClear(renderer);
}


bool KeyPressed(MathEquation eq) {
    SDL_Event player_input;
    char ans_char = ' ';
    Uint32 start_time = SDL_GetTicks();
    int count_tick = 0;
    int key;
    unsigned int time_limit;
    key = 10;
    time_limit = 800;
    while (SDL_GetTicks() - start_time <= time_limit) {
        if (SDL_PollEvent(&player_input) != 0 && player_input.type == SDL_KEYDOWN) {
            if (player_input.key.keysym.sym == SDLK_LEFT) {
                ans_char = 'N';
                break;
            }
            if (player_input.key.keysym.sym == SDLK_RIGHT) {
                ans_char = 'Y';
                break;
            }
        }
        if (count_tick > key) {
            key += count_tick;
            count_tick++;
        }
        count_tick++;
    }
    return ans_char == eq.key_;
}

std::string GetPointString(int point) {
    std::string final_string;
    std::stringstream ss;
    ss << point;
    final_string = ss.str();
    return final_string;
}

void GameOver(int point);

bool TimeDiscounting(MathEquation eq) {
    return KeyPressed(eq);
}
void StartARound(int point) {
    if (point == 0) {
        Intro();
    } else {
        game_print.resetAfterARound();
    }
    MathEquation eq;
    eq.getEquation();
    PrintEq(eq);
    if (TimeDiscounting(eq)) {
        point++;
        StartARound(point);
    } else {
        GameOver(point);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PrintMenu() {
    const std::vector<int> start_button{40, 300, 145, 63};
    const std::vector<int> quit_button{210, 300, 145, 62};
    game_print.getImage("../images/menu.png");
    game_print.getButton("../images/startButton.png", start_button[0], start_button[1], start_button[2], start_button[3]);
    game_print.getButton("../images/quitButton.png", quit_button[0], quit_button[1], quit_button[2], quit_button[3]);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouse_x = e.button.x;
            int mouse_y = e.button.y;
            if ((mouse_x > start_button[0]) && (mouse_x < start_button[0] + start_button[2]) &&
                (mouse_y > start_button[1]) && (mouse_y < start_button[1] + start_button[3])) {
                SDL_RenderClear(renderer);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                StartARound(0);
                quit = true;
            }
            if ((mouse_x > quit_button[0]) && (mouse_x < quit_button[0] + quit_button[2]) &&
                (mouse_y > quit_button[1]) && (mouse_y < quit_button[1] + quit_button[3])) {
                quit = true;
            }
        }
    }
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameOver(int point) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    game_print.initWindow();
    over_music.Load("../sounds/gameOver.wav");
    over_music.Play();
    game_print.getImage("../images/endGame1.png");
    SDL_Delay(800);
    game_print.getImage("../images/endGame2.png");
    SDL_Delay(800);
    game_print.getImage("../images/endGame3.png");
    SDL_Delay(800);
    game_print.getImage("../images/endGame4.png");
    game_print.printScore(GetPointString(point));
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } else {
                over_music.Stop();
                SDL_RenderClear(renderer);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                StartARound(0);
                quit = true;
            }
        }
    }
    over_music.Stop();
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int main() {
    game_print.initWindow();
    PrintMenu();
    return 0;
}