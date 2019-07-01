#include <iostream>

#include "Game.h"

Game* game = NULL;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char *argv[]) {
    Uint32 frameStart, frameTime;
    std::cout << "game init attempt...\n" << std::endl;

    const char windowTitle[] = "Hibiki Game Engine";
    if(TheGame::getInstance()->init(windowTitle, 100, 100, 640, 480, false)) {
        std::cout << "game init success!\n" << std::endl;

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
        std::cout << "game init failure - " << SDL_GetError() << "\n" << std::endl;
        return -1;
    }

    std::cout << "game closing...\n" << std::endl;
    TheGame::getInstance()->clean();
    return 0;
}