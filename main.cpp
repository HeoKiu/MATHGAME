#include "MathEquation.h"
#include "Sound.h"
#include "drawer.h"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <sstream>


SDL_Window *gWindow;
SDL_Renderer *gRenderer;
drawer gameDraw(gWindow, gRenderer);
Sound openSound;
Sound overSound;
Sound defuseSound;
Sound inGameSound;

void printIntro() {
    gameDraw.initWindow();
    openSound.Load("planting.wav");
    defuseSound.Load("defusing.wav");
    openSound.Play();
    for (size_t i = 0; i < 8; i++) {
        gameDraw.getImage("introScene1.png");
        SDL_Delay(100);
        gameDraw.getImage("introScene2.png");
        SDL_Delay(100);
    }
    gameDraw.getImage("introScene3.png");
    SDL_Delay(500);
    gameDraw.getImage("introScene4.png");
    SDL_Delay(250);
    gameDraw.getImage("introScene5.png");
    SDL_Delay(1600);
    defuseSound.Play();
    gameDraw.getImage("defusing.png");
    SDL_Delay(1300);
    defuseSound.Stop();
    openSound.Stop();
    SDL_RenderClear(gRenderer);
}

std::string getStringEquation(MathEquation eq) {
    std::string finalString;
    std::stringstream ss;
    ss << eq.first_number_;
    finalString = ss.str();
    std::stringstream ss2;
    ss2 << eq.second_number_;
    finalString = finalString + " + " + ss2.str();
    std::stringstream ss3;
    ss3 << eq.third_number_;
    finalString = finalString + " = " + ss3.str();
    return finalString;
}

void printEq(MathEquation eq) {
    gameDraw.getImage("defusing.png");
    inGameSound.Load("imgame.wav");
    inGameSound.Play();
    SDL_Delay(500);
    gameDraw.printEquation(getStringEquation(eq));
    gameDraw.getButton("wrong.png", 30, 400, 165, 145);
    gameDraw.getButton("right.png", 210, 400, 165, 145);
    gameDraw.clearRender();
    inGameSound.Stop();
}

bool aKeyPressed(MathEquation eq, int point) {
    SDL_Event playerAns;
    char ansChar = ' ';
    Uint32 startTime = SDL_GetTicks();
    size_t lastWidth = 0;
    size_t countTick = 0;
    size_t key;
    size_t timeLimit;
    size_t step = 46;
    if (point < 5) {
        timeLimit = 2500;
        key = 30;
    } else {
        timeLimit = 1000;
        key = 10;
    }
    while (SDL_GetTicks() - startTime <= timeLimit) {

        if (SDL_PollEvent(&playerAns) != 0 && playerAns.type == SDL_KEYDOWN) {
            if (playerAns.key.keysym.sym == SDLK_LEFT) {
                ansChar = 'N';
                break;
            }
            if (playerAns.key.keysym.sym == SDLK_RIGHT) {
                ansChar = 'Y';
                break;
            }
        }
        if (countTick > key) {
            lastWidth += step;
            key += countTick;
            countTick++;
        }
        countTick++;
    }
    if (ansChar == eq.key_) return true;
    return false;
}

std::string getPointString(size_t point) {
    std::string finalString;
    std::stringstream ss;
    ss << point;
    finalString = ss.str();
    return finalString;
}

void gameOver(size_t point);

bool timeDiscounting(MathEquation eq, size_t point) {
    if (aKeyPressed(eq, point)) {
        return true;
    }
    return false;
}

void startARound(int point) {
    if (point == 0) {
        printIntro();
    } else {
        gameDraw.resetAfterARound();
    }
    int lv;
    if (point > 5) {
        if (point > 10) {
            lv = 3;
        } else
            lv = 2;
    } else
        lv = 1;
    MathEquation eq;
    eq.getEquation(lv);
    printEq(eq);
    if (timeDiscounting(eq, point)) {
        point++;
        startARound(point);
    } else
        gameOver(point);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
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
    gameDraw.getImage("menu.png");
    gameDraw.getButton("startButton.png", statButtonX, startButtonY, startButtonW, startButtonH);
    gameDraw.getButton("quitButton.png", quitButtonX, quitButtonY, quitButtonW, quitButtonH);
    bool quit = false;
    SDL_Event e;
    while (!quit) {

        if (SDL_PollEvent(&e) != 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if ((mouseX > statButtonX) && (mouseX < statButtonX + startButtonW) &&
                (mouseY > startButtonY) && (mouseY < startButtonY + startButtonH)) {
                SDL_RenderClear(gRenderer);
                SDL_DestroyRenderer(gRenderer);
                SDL_DestroyWindow(gWindow);
                SDL_Quit();
                startARound(0);
                quit = true;
            }
            if ((mouseX > quitButtonX) && (mouseX < quitButtonX + quitButtonW) &&
                (mouseY > quitButtonY) && (mouseY < quitButtonY + quitButtonH))
                quit = true;
        }
    }
    SDL_RenderClear(gRenderer);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    gameDraw.initWindow();
    printMenu();
    return 0;
}

void gameOver(int point) {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    gameDraw.initWindow();
    overSound.Load("gameOver.wav");
    overSound.Play();
    gameDraw.getImage("endGame1.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame2.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame3.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame4.png");
    gameDraw.printScore(getPointString(point));
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } else {
                overSound.Stop();
                SDL_RenderClear(gRenderer);
                SDL_DestroyRenderer(gRenderer);
                SDL_DestroyWindow(gWindow);
                SDL_Quit();
                startARound(0);
                quit = true;
            }
        }
    }
    overSound.Stop();
    SDL_RenderClear(gRenderer);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}