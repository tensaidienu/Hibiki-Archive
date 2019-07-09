#include <iostream>
#include <map>

#include "GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "GameOverState.h"

GameStateMachine::GameStateMachine() {

}

void GameStateMachine::initialState() {
    gameState = new MainMenuState();
    gameState->onEnter();
}

void GameStateMachine::changeState(Hibiki_GameState type) {
    switch (type) {
        case HIBIKI_MAIN_MENU:
            wait = true;
            gameState->onExit();
            tempGameState = gameState;
            gameState = new MainMenuState();
            gameState->onEnter();
            delete tempGameState;
            wait = false;
            break;
        case HIBIKI_PLAY:
            wait = true;
            gameState->onExit();
            tempGameState = gameState;
            gameState = new PlayState();
            gameState->onEnter();
            delete tempGameState;
            wait = false;
            break;
        case HIBIKI_PAUSE:
            std::cout << "Pause";
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
            wait = false;
            break;
    }
    std::cout << "Change state: " << gameState->getStateID() << std::endl;
}

void GameStateMachine::pauseToMain() {
    std::cout << "pauseToMain";
    wait = true;
    GameState* tempPauseState = gameState;
    tempPauseState->onExit();
    tempGameState->onExit();
    gameState = new MainMenuState();
    gameState->onEnter();
    delete tempPauseState;
    delete tempGameState;
    wait = false;
}

void GameStateMachine::resumePlay() {
    std::cout << "resumePlay";
    wait = true;    
    GameState* tempPlayState = tempGameState;
    tempGameState = gameState;
    tempGameState->onExit();
    gameState = tempPlayState;
    delete tempGameState;
    wait = false;
}

void GameStateMachine::update() {
    if(!wait){
        gameState->update();
    }
}

void GameStateMachine::render() {
    if(!wait){
        gameState->render();
    }
}

GameStateMachine::~GameStateMachine() {
    delete gameState;
    delete tempGameState;
}