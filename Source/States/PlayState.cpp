#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"
#include "../Managers/InputManager.h"
#include "../Levels/LevelParser.h"

#include "PlayState.h"
#include "StateParser.h"

const std::string PlayState::playID = "PLAY";

PlayState::PlayState() { }

void PlayState::update() {
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PAUSE);
    }

    level->update();

    /*if(checkCollision(dynamic_cast<DynamicGameObject*> (gameObjects[0]), dynamic_cast<DynamicGameObject*> (gameObjects[1]))) {
        TheGame::getInstance()->getStateMachine()->pushState(new GameOverState());
    }*/
}

void PlayState::render() {
    level->render();
}

bool PlayState::onEnter() {
    LevelParser levelParser;
    level = levelParser.parseLevel(PATH_MAPS+"TensaiMap.tmx");
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    // clear the texture manager
    for(int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }
    level->clear();
    std::cout << "exiting PlayState\n" << std::endl;
    return true;
}

PlayState::~PlayState() {
    delete level;
}