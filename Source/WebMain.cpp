#include <emscripten.h>
#include <emscripten/html5.h>

#include <iostream>

#include "SDL2/SDL.h"

#include "GameController.h"

struct context { int x; };

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
context ctx;
Uint32 frameStart, frameTime;

/**
 * The loop handler, will be called repeatedly
 */
void loop_fn(void *arg) {
    if(!TheGame::getInstance()->isGameRunning()) {
        emscripten_cancel_main_loop();
    }

    frameStart = SDL_GetTicks();

    TheGame::getInstance()->handleEvents();
    TheGame::getInstance()->update();
    TheGame::getInstance()->render();

    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < DELAY_TIME) {
        SDL_Delay((int)(DELAY_TIME - frameTime));
    }
}

int main(int argc, char *argv[]) {
    context ctx;
    int simulate_infinite_loop = 1;
    ctx.x = 0;

    SDL_Log("Game init attempt...");
    const char windowTitle[] = "Hibiki Game Engine - ALPHA Version 0.0.3";
    if(TheGame::getInstance()->init(windowTitle, 550, 100, 640, 480, SDL_WINDOW_SHOWN)) {
        SDL_Log("Game init success!");
    } else {
        SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Game init failure - %s", SDL_GetError());
        return -1;
    }

    emscripten_set_main_loop_arg(loop_fn, &ctx, -1, simulate_infinite_loop);

    /**
     * If simulate_infinite_loop = 0, emscripten_set_main_loop_arg won't block
     * and this code will run straight away.
     * If simulate_infinite_loop = 1 then this code will not be reached
     */
    SDL_Log("Game closing...");
    TheGame::getInstance()->clear();
    return 0;
}