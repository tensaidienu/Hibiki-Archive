#include <iostream>
#include <map>

#include "SDL2/SDL.h"

#include "GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "GameOverState.h"

GameStateMachine::GameStateMachine() {

}

GameStateMachine::~GameStateMachine() {
    delete gameState;
    delete tempGameState;
    gameState = nullptr;
    tempGameState = nullptr;
}

void GameStateMachine::initialState() {
    gameState = new MainMenuState();
    gameState->onEnter();
}

void GameStateMachine::changeState(HibikiGameState type) {
    switch (type) {
        case HIBIKI_MAIN_MENU:
            wait = true;
            gameState->onExit();
            tempGameState = gameState;
            gameState = new MainMenuState();
            gameState->onEnter();
            delete tempGameState;
            tempGameState = nullptr;
            wait = false;
            break;
        case HIBIKI_PLAY:
            wait = true;
            gameState->onExit();
            tempGameState = gameState;
            gameState = new PlayState();
            gameState->onEnter();
            //delete tempGameState;
            //tempGameState = nullptr;
            wait = false;
            break;
        case HIBIKI_PAUSE:
            SDL_Log("Game Paused");
            tempGameState = gameState;
            gameState = new PauseState();
            gameState->onEnter();
            break;
        case HIBIKI_GAME_OVER:
            wait = true;
            gameState->onExit();
            tempGameState = gameState;
            gameState = new GameOverState();
            gameState->onEnter();
            delete tempGameState;
            tempGameState = nullptr;
            wait = false;
            break;
    }
    SDL_Log("Change state: %s", gameState->getStateID().c_str());
}

void GameStateMachine::pauseToMain() {
    wait = true;
    GameState* tempPauseState = gameState;
    tempPauseState->onExit();
    tempGameState->onExit();
    gameState = new MainMenuState();
    gameState->onEnter();
    delete tempPauseState;
    delete tempGameState;
    tempPauseState = nullptr;
    tempGameState = nullptr;
    wait = false;
}

void GameStateMachine::resumePlay() {
    wait = true;
    GameState* tempPlayState = tempGameState;
    tempGameState = gameState;
    tempGameState->onExit();
    gameState = tempPlayState;
    delete tempGameState;
    tempGameState = nullptr;
    wait = false;
}

void GameStateMachine::update() {
    if(!wait && gameState){
        gameState->update();
    }
}

void GameStateMachine::render() {
    if(!wait && gameState){
        gameState->render();
    }
}