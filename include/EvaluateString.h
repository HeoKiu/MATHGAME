
//
// Created by duc on 20.12.2021.
//

#include <iostream>
#include <sstream>
#include "../include/MathEquation.h"
#include <SDL.h>

class EvaluateString {
public:
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
    std::string GetPointString(int point) {
        std::string final_string;
        std::stringstream ss;
        ss << point;
        final_string = ss.str();
        return final_string;
    }
    bool KeyPressed(MathEquation eq) {
        size_t key = 10;
        const size_t time_limit = 800;
        SDL_Event player_input;
        char ans_char = ' ';
        Uint32 start_time = SDL_GetTicks();
        int count_tick = 0;
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

    bool TimeDiscounting(MathEquation eq) {
        EvaluateString temp;
        return temp.KeyPressed(eq);
    }
};




