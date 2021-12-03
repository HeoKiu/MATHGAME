#include "Drawer.h"
#include "MathEquation.h"
#include "Music.h"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <sstream>
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
    const std::vector<int> rightButton{210, 400, 165, 145};
    inGameMusic.Load("imgame.wav");
    gamePrint.getImage("defusing.png");
    inGameMusic.Play();
    SDL_Delay(delayTime);
    gamePrint.printEquation(getStringEquation(eq));
    gamePrint.getButton("wrong.png", wrongButton[1], wrongButton[2], wrongButton[3], wrongButton[4]);
    gamePrint.getButton("right.png", rightButton[1], rightButton[2], rightButton[3], rightButton[4]);
    gamePrint.clearRender();
    inGameMusic.Stop();
}

void Intro() {
    //Print intro with sound from source , the delay time is made to fit with the length of the sound
    int numberImages = 8;
    gamePrint.initWindow();
    const size_t delayTimeIntro = 100;
    const size_t delayTimeIntro2 = 500;
    const size_t delayTimeIntro3 = 250;
    const size_t delayTimeIntro4 = 1600;
    const size_t delayTimeIntro5 = 1300;
    openMusic.Load("planting.wav");
    defuseMusic.Load("defusing.wav");
    openMusic.Play();
    while (numberImages-- > 0) {
        gamePrint.getImage("introScene1.png");
        SDL_Delay(delayTimeIntro);
        gamePrint.getImage("introScene2.png");
        SDL_Delay(delayTimeIntro);
    }
    gamePrint.getImage("introScene3.png");
    SDL_Delay(delayTimeIntro2);
    gamePrint.getImage("introScene4.png");
    SDL_Delay(delayTimeIntro3);
    gamePrint.getImage("introScene5.png");
    SDL_Delay(delayTimeIntro4);
    defuseMusic.Play();
    gamePrint.getImage("defusing.png");
    SDL_Delay(delayTimeIntro5);
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
    timeLimit = 1500;
    while (SDL_GetTicks() - startTime <= timeLimit) {
        if (playerInput.type == SDL_KEYDOWN && SDL_PollEvent(&playerInput) != 0) {
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
            key = key + countTick;
            countTick++;
        }
        countTick++;
    }
    if (ansChar == eq.key_) { return true; }
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

void newRound(int point) {
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
        newRound(point);
    } else
        gameOver(point);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void printMenu() {
    const int statButtonX = 40;
    const int startButtonY = 300;
    const int startButtonW = 145;
    const int startButtonH = 63;
    const int quitButtonX = 210;
    const int quitButtonY = 300;
    const int quitButtonW = 145;
    const int quitButtonH = 62;
    gamePrint.getImage("menu.png");
    gamePrint.getButton("startButton.png", statButtonX, startButtonY, startButtonW, startButtonH);
    gamePrint.getButton("quitButton.png", quitButtonX, quitButtonY, quitButtonW, quitButtonH);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if ((mouseX > statButtonX) && (mouseX < statButtonX + startButtonW) &&
                (mouseY > startButtonY) && (mouseY < startButtonY + startButtonH)) {
                SDL_RenderClear(Renderer);
                SDL_DestroyRenderer(Renderer);
                SDL_DestroyWindow(Window);
                SDL_Quit();
                newRound(0);
                quit = true;
            }
            if ((mouseX > quitButtonX) && (mouseX < quitButtonX + quitButtonW) &&
                (mouseY > quitButtonY) && (mouseY < quitButtonY + quitButtonH))
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
                newRound(0);
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
