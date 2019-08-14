#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"
#include "../Managers/InputManager.h"
#include "../Levels/LevelParser.h"

#include "PlayState.h"
#include "StateParser.h"

const std::string PlayState::playID = "PLAY";

PlayState::PlayState(){}

PlayState::~PlayState() {
    delete level;
}

void PlayState::update() {
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PAUSE);
    }

    this->level->update();

    /*if(checkCollision(dynamic_cast<DynamicGameObject*> (gameObjects[0]), dynamic_cast<DynamicGameObject*> (gameObjects[1]))) {
        TheGame::getInstance()->getStateMachine()->pushState(new GameOverState());
    }*/
}

void PlayState::render() {
    //level->render();
    if (this->level) {
        this->level->render();
    }
}

bool PlayState::onEnter() {
    LevelParser levelParser;
    this->level = levelParser.parseLevel(PATH_MAPS+"TensaiMap.tmx");
    SDL_Log("Entering PlayState");
    return true;
}

bool PlayState::onExit() {
    // clear the texture manager
    for(int i = 0; i < this->textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(this->textureIDList[i]);
    }
    this->level->clear();
    SDL_Log("Exiting PlayState");
    return true;
}