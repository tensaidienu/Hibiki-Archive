#include <iostream>

#include "PauseState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain() {
    TheGame::getInstance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::resumePlay() {
    TheGame::getInstance()->getStateMachine()->popState();
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
    stateParser.parseState("../Assets/test.xml", pauseID, &gameObjects, &textureIDList);
    callbacks.push_back(pauseToMain);
    callbacks.push_back(resumePlay);
    setCallbacks(callbacks);
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
    TheInputHandler::getInstance()->reset();
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks) {
    // go through the game objects
    for(int i = 0; i < gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {            
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);
        }
    }
}