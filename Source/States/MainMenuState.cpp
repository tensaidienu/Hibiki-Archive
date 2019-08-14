#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"

#include "../GameObjects/MenuButton.h"

#include "MainMenuState.h"
#include "StateParser.h"

const std::string MainMenuState::menuID = "MENU";

MainMenuState::MainMenuState(){}

MainMenuState::~MainMenuState() {
    SDL_Log("Cleaning MainMenuState");
    for (auto gameObject : gameObjects) {
        delete gameObject;
    }
    gameObjects.clear();
}

void MainMenuState::update() {
    SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 0, 0, 0);
    for (int x = 0; x < gameObjects.size(); x++) {
        gameObjects[x]->update();
    }
}

void MainMenuState::render() {
    for (int x = 0; x < gameObjects.size(); x++) {
        gameObjects[x]->draw();
    }
}

bool MainMenuState::onEnter() {
    StateParser stateParser;
    stateParser.parseState(PATH_GUI + "Menu.xml", menuID, &gameObjects, &textureIDList);

    functionCallbacks.emplace("menuToPlay", menuToPlay);
    functionCallbacks.emplace("exitFromMenu", exitFromMenu);

    // set the callbacks for menu items
    setCallbacks();
    return true;
}

bool MainMenuState::onExit() {
    SDL_Log("onExit Cleaning MainMenuState");
    for (int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }
    return true;
}

void MainMenuState::menuToPlay() {
    SDL_Log("Play button clicked");
    TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PLAY);
}

void MainMenuState::exitFromMenu() {
    SDL_Log("Exit button clicked");
    TheGame::getInstance()->setGameRunning(false);
}

void MainMenuState::setCallbacks() {
    // go through the game objects
    for (int i = 0; i < gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based on the id
        // passed in from the file
        if (dynamic_cast<MenuButton*>(gameObjects[i])) {
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setFuncCallback(functionCallbacks[button->getCallbackID()]);
        }
    }
}