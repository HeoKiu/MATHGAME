#include "../include/Drawer.h"
#include "../include//MathEquation.h"
#include "../include//Music.h"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

SDL_Window *Window;
SDL_Renderer *Renderer;
Drawer gamePrint(Window, Renderer);
Music openMusic;
Music overMusic;
Music defuseMusic;
Music inGameMusic;

std::string getStringEquation(MathEquation equation) {
    std::string finalString;
    std::stringstream secondValue;
    std::stringstream firstValue;
    std::stringstream thirdValue;
    firstValue << equation.firstNumber;
    finalString = firstValue.str();
    secondValue << equation.secondNumber;
    finalString = finalString + " + " + secondValue.str();
    thirdValue << equation.thirdNumber;
    finalString = finalString + " = " + thirdValue.str();
    return finalString;
}

void printEq(MathEquation eq) {
    const size_t delayTime = 500;
    const std::vector<int> wrongButton{30, 400, 165, 145};
    const std::vector<int> rightButoon{210, 400, 165, 145};
    inGameMusic.Load("imgame.wav");
    gamePrint.getImage("defusing.png");
    inGameMusic.Play();
    SDL_Delay(delayTime);
    gamePrint.printEquation(getStringEquation(eq));
    gamePrint.getButton("wrong.png", wrongButton[0], wrongButton[1], wrongButton[2], wrongButton[3]);
    gamePrint.getButton("right.png", rightButoon[0], rightButoon[1], rightButoon[2], rightButoon[3]);
    gamePrint.clearRender();
    inGameMusic.Stop();
}

void Intro() {
    int numberImages = 8;
    gamePrint.initWindow();
    const std::vector<int> delayTime{100, 500, 250, 1600, 1300};
    openMusic.Load("planting.wav");
    defuseMusic.Load("defusing.wav");
    openMusic.Play();
    while (numberImages-- > 0) {
        gamePrint.getImage("introScene1.png");
        SDL_Delay(delayTime[0]);
        gamePrint.getImage("introScene2.png");
        SDL_Delay(delayTime[0]);
    }
    gamePrint.getImage("introScene3.png");
    SDL_Delay(delayTime[1]);
    gamePrint.getImage("introScene4.png");
    SDL_Delay(delayTime[2]);
    gamePrint.getImage("introScene5.png");
    SDL_Delay(delayTime[3]);
    defuseMusic.Play();
    gamePrint.getImage("defusing.png");
    SDL_Delay(delayTime[4]);
    defuseMusic.Stop();
    openMusic.Stop();
    SDL_RenderClear(Renderer);
}


bool aKeyPressed(MathEquation eq) {
    SDL_Event playerInput;
    char ansChar = ' ';
    Uint32 startTime = SDL_GetTicks();
    int countTick = 0;
    int key;
    unsigned int timeLimit;
    key = 10;
    timeLimit = 800;
    while (SDL_GetTicks() - startTime <= timeLimit) {
        if (SDL_PollEvent(&playerInput) != 0 && playerInput.type == SDL_KEYDOWN) {
            if (playerInput.key.keysym.sym == SDLK_LEFT) {
                ansChar = 'N';
                break;
            }
            if (playerInput.key.keysym.sym == SDLK_RIGHT) {
                ansChar = 'Y';
                break;
            }
        }
        if (countTick > key) {
            key += countTick;
            countTick++;
        }
        countTick++;
    }
    if (ansChar == eq.key_) return true;
    return false;
}

std::string getPointString(int point) {
    std::string finalString;
    std::stringstream ss;
    ss << point;
    finalString = ss.str();
    return finalString;
}

void gameOver(int point);

bool timeDiscounting(MathEquation eq, int point) {
    if (!aKeyPressed(eq)) {
        return false;
    }
    return true;
}
void startARound(int point) {
    if (point == 0) {
        Intro();
    } else {
        gamePrint.resetAfterARound();
    }
    MathEquation eq;
    eq.getEquation();
    printEq(eq);
    if (timeDiscounting(eq, point)) {
        point++;
        startARound(point);
    } else
        gameOver(point);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void printMenu() {
    const std::vector<int> startButton{40, 300, 145, 63};
    const std::vector<int> quitButton{210, 300, 145, 62};
    gamePrint.getImage("menu.png");
    gamePrint.getButton("startButton.png", startButton[0], startButton[1], startButton[2], startButton[3]);
    gamePrint.getButton("quitButton.png", quitButton[0], quitButton[1], quitButton[2], quitButton[3]);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if ((mouseX > startButton[0]) && (mouseX < startButton[0] + startButton[2]) &&
                (mouseY > startButton[1]) && (mouseY < startButton[1] + startButton[3])) {
                SDL_RenderClear(Renderer);
                SDL_DestroyRenderer(Renderer);
                SDL_DestroyWindow(Window);
                SDL_Quit();
                startARound(0);
                quit = true;
            }
            if ((mouseX > quitButton[0]) && (mouseX < quitButton[0] + quitButton[2]) &&
                (mouseY > quitButton[1]) && (mouseY < quitButton[1] + quitButton[3]))
                quit = true;
        }
    }
    SDL_RenderClear(Renderer);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void gameOver(int point) {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    gamePrint.initWindow();
    overMusic.Load("gameOver.wav");
    overMusic.Play();
    gamePrint.getImage("endGame1.png");
    SDL_Delay(800);
    gamePrint.getImage("endGame2.png");
    SDL_Delay(800);
    gamePrint.getImage("endGame3.png");
    SDL_Delay(800);
    gamePrint.getImage("endGame4.png");
    gamePrint.printScore(getPointString(point));
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } else {
                overMusic.Stop();
                SDL_RenderClear(Renderer);
                SDL_DestroyRenderer(Renderer);
                SDL_DestroyWindow(Window);
                SDL_Quit();
                startARound(0);
                quit = true;
            }
        }
    }
    overMusic.Stop();
    SDL_RenderClear(Renderer);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
int main() {
    gamePrint.initWindow();
    printMenu();
    return 0;
}