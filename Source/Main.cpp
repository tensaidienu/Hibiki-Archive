#include <iostream>

#include "SDL2/SDL.h"

#include "GameController.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char *argv[]) {
    Uint32 frameStart, frameTime;
    SDL_Log("MAIN - Game init attempt...");

    //const char windowTitle[] = "Hibiki Game Engine";
    std::string windowTitle = "Hibiki Game Engine - ALPHA Version 0.0.3";
    if(TheGame::getInstance()->init(windowTitle, 550, 100, 640, 480, SDL_WINDOW_RESIZABLE)) {
        SDL_Log("MAIN - Game init success!");

        while(TheGame::getInstance()->isGameRunning()) {
            frameStart = SDL_GetTicks();

            TheGame::getInstance()->handleEvents();
            TheGame::getInstance()->update();
            TheGame::getInstance()->render();

            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }

    } else {
        SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "MAIN - Game init failure - %s", SDL_GetError());
        return -1;
    }

    SDL_Log("MAIN - Game closing...");
    TheGame::getInstance()->clear();
    return 0;
}