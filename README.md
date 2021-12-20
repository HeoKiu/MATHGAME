# Game_MIPT_SDL2
## Description

A Game, using C++ and SDL 2.0

A math game

## Requirements 

You need the following tools to build this project:
* CMake
* Make 
* SDL 2.0, SDL2_image, SDL2_ttf, SDL2_mixer (For Debian: `sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev`)
* googletest

## What's news?
Add clang-tidy and clang-format to maintain code style, change layout, put all graphic files and sound files, font files in a place, and set up googletest.

## Build instructions
Git clone the project, remember to git clone this branch =)))

## Atention
You should download googletest on Github by yourself. After that, create a folder "lib" in the directory and but the googletest there to make sure it run smoothly. 

## Game instructions
Change the directory to the "Game_MIPT_SDL2" folder and create a new folder "build":
```
cd build
```
Then start cmake:
```
cmake ..
```
Now run make
```
make
```
To run the project, type:
```
./GameSDL
```
## Test instructions

```
make tests
```
```
cd tests
```
```
./tests
```


Have Fun !!!
