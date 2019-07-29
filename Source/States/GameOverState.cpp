#include "GameOverState.h"

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../GameObjects/AnimatedGraphic.h"
#include "../GameObjects/MenuButton.h"

#include "../Managers/TextureManager.h"

#include "StateParser.h"

const std::string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::update(){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void GameOverState::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter() {
	StateParser stateParser;
	stateParser.parseState("../Assets/test.xml", gameOverID, &gameObjects, &textureIDList);

	functionCallbacks.emplace("gameOverToMain", gameOverToMain);
    functionCallbacks.emplace("restartPlay", restartPlay);
    
	// set the callbacks for menu items
    setCallbacks();
    return true;
}

bool GameOverState::onExit() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();

	for (int i = 0; i < textureIDList.size(); i++) {
		TheTextureManager::getInstance()->clearFromTextureMap(textureIDList[i]);
	}

	return true;
}

void GameOverState::gameOverToMain() {
	TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_MAIN_MENU);
}

void GameOverState::restartPlay() {
	TheGame::getInstance()->getStateMachine()->changeState(HIBIKI_PLAY);
}

void GameOverState::setCallbacks() {
    // go through the game objects
    for(int i = 0; i < gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setFuncCallback(functionCallbacks[button->getCallbackID()]);
        }
    }
}