#include <emscripten.h>
#include <emscripten/html5.h>

#include <iostream>

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

    std::cout << "game init attempt...\n" << std::endl;
    const char windowTitle[] = "Hibiki Game Engine";
    if(TheGame::getInstance()->init(windowTitle, 550, 100, 640, 480, SDL_WINDOW_SHOWN)) {
        std::cout << "game init success!\n" << std::endl;
    } else {
        std::cout << "game init failure - " << SDL_GetError() << "\n" << std::endl;
        return -1;
    }

    emscripten_set_main_loop_arg(loop_fn, &ctx, -1, simulate_infinite_loop);

    /**
     * If simulate_infinite_loop = 0, emscripten_set_main_loop_arg won't block
     * and this code will run straight away.
     * If simulate_infinite_loop = 1 then this code will not be reached
     */
    printf("quitting...\n");

    std::cout << "game closing...\n" << std::endl;
    TheGame::getInstance()->clean();
    return 0;
}