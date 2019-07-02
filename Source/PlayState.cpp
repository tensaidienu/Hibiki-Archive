#include <iostream>

#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "InputHandler.h"
#include "LevelParser.h"

const std::string PlayState::playID = "PLAY";

void PlayState::update() {
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::getInstance()->getStateMachine()->pushState(new PauseState());
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
    // parse the state
    /*StateParser stateParser;
    stateParser.parseState("../Assets/test.xml", playID, &gameObjects, &textureIDList);*/

    LevelParser levelParser;
    level = levelParser.parseLevel("../Assets/SDL/TensaiMap5.tmx");
    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::onExit() {
    // clear the texture manager
    /*for(int i = 0; i < textureIDList.size(); i++) {
        TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
    }*/
    /*for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->clean();
    }
    gameObjects.clear();
    TheTextureManager::getInstance()->clearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n" << std::endl;*/
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