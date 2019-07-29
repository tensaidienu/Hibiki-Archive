#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"
#include "../Managers/InputManager.h"

#include "../GameObjects/MenuButton.h"

#include "PauseState.h"
#include "StateParser.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain() {
    TheGame::getInstance()->getStateMachine()->pauseToMain();
    //TheGame::getInstance()->getStateMachine()->popState();
    //TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_MAIN_MENU);
}

void PauseState::resumePlay() {
    TheGame::getInstance()->getStateMachine()->resumePlay();
    //TheGame::getInstance()->getStateMachine()->popState();
}

void PauseState::update() {
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->update();
    }
}

void PauseState::render() {
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->draw();
    }
}

bool PauseState::onEnter() {
    StateParser stateParser;
    std::cout << PATH_GUI+"Pause.xml" << std::endl;
    stateParser.parseState(PATH_GUI + "Pause.xml", pauseID, &gameObjects, &textureIDList);

    functionCallbacks.emplace("pauseToMain", pauseToMain);
    functionCallbacks.emplace("resumePlay", resumePlay);
    
    // set the callbacks for menu items
    setCallbacks();
    return true;
}

bool PauseState::onExit() {
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->clean();
    }
    gameObjects.clear();
    // clear the texture manager
    for(int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }
    // reset the mouse button states to false
    TheInputManager::getInstance()->reset();
    return true;
}

void PauseState::setCallbacks() {
    // go through the game objects
    for(int i = 0; i < gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {            
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setFuncCallback(functionCallbacks[button->getCallbackID()]);
        }
    }
}