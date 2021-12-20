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
Add clang-tidy to maintain code style, change layout and set up googletest.

## Build instructions
Git clone the project, remember to git clone this branch =)))

You download googletest on Github. After that, create a folder "lib" in the directory and but the googletest there. 

Create a new folder "build"

Change the directory to the "Game_MIPT_SDL2" folder:
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
cd tests
```
./tests
```


Have Fun !!!
