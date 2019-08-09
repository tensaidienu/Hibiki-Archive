#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"

#include "../GameObjects/MenuButton.h"

#include "MainMenuState.h"
#include "StateParser.h"

const std::string MainMenuState::menuID = "MENU";

MainMenuState::MainMenuState() { }

void MainMenuState::update() {
    SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 0, 0, 0);
    for(int x = 0; x < gameObjects.size(); x++) {
        gameObjects[x]->update();
    }
}

void MainMenuState::render() {
    for(int x = 0; x < gameObjects.size(); x++) {
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
    // clear the texture manager
    for(int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }
    for(int x = 0; x < gameObjects.size(); x++) {
        gameObjects[x]->clean();
    }
    gameObjects.clear();
    /*
    TheTextureManager::getInstance()->clearFromTextureMap("playbutton");
    TheTextureManager::getInstance()->clearFromTextureMap("exitbutton");
    std::cout << "exiting MainMenuState\n" << std::endl;
    */
    return true;
}

void MainMenuState::menuToPlay() {
    std::cout << "Play button clicked\n" << std::endl;
    TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PLAY);
}

void MainMenuState::exitFromMenu() {
    std::cout << "Exit button clicked\n" << std::endl;
    TheGame::getInstance()->clean();
}

void MainMenuState::setCallbacks() {
    // go through the game objects
    for(int i = 0; i < gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {            
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setFuncCallback(functionCallbacks[button->getCallbackID()]);
        }
    }
}

MainMenuState::~MainMenuState() {
    for (auto it : gameObjects) {
        delete it;
    }
}