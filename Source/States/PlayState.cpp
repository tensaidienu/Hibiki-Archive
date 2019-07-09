#include <iostream>

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"
#include "../Managers/InputManager.h"
#include "../Levels/LevelParser.h"

#include "PlayState.h"
#include "StateParser.h"

const std::string PlayState::playID = "PLAY";

PlayState::PlayState(){

}

void PlayState::update() {
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PAUSE);
        //TheGame::getInstance()->getStateMachine()->pushState("Pause");
        //TheGame::getInstance()->getStateMachine()->pause();
    }

    level->update();

    /*for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->update();
    }*/

    /*if(checkCollision(dynamic_cast<SDLGameObject*> (gameObjects[0]), dynamic_cast<SDLGameObject*> (gameObjects[1]))) {
        TheGame::getInstance()->getStateMachine()->pushState(new GameOverState());
    }*/
}

void PlayState::render() {
    level->render();
    /*for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->draw();
    }*/
}

bool PlayState::onEnter() {
    LevelParser levelParser;
    level = levelParser.parseLevel("../Assets/SDL/TensaiMap5.tmx");
    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::onExit() {
    // clear the texture manager
    for(int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->clean();
    }    
    gameObjects.clear();
    level->clear();
    std::cout << "exiting PlayState\n" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2) {
    /*int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
 
    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();
    //Calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();
    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false; }
    if( rightA <= leftB ){return false; }
    if( leftA >= rightB ){return false;}*/
    return true;
}

PlayState::~PlayState() {
    delete level;
    for (auto it : gameObjects) {
        delete it;
    }
    gameObjects.clear();
}