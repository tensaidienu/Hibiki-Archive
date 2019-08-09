#include <iostream>

#include "GameController.h"
#include "GlobalVariables.h"

#include "Managers/TextureManager.h"
#include "Managers/InputManager.h"

#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/MenuButton.h"
#include "GameObjects/AnimatedGraphic.h"
#include "GameObjects/StaticGameObject.h"

using namespace std;

GameController* GameController::gameInstance = 0;

GameController::GameController() {
   mainWindow   = NULL;
   renderer = NULL;
   gameRunning  = true;
}

GameController::~GameController() {

}

bool GameController::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    //flags = SDL_WINDOW_RESIZABLE;
    //flags = SDL_WINDOW_SHOWN;
	gameWidth = width;
	gameHeight = height;

    // attempt to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "SDL init success");
        
        mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(mainWindow != NULL) {
            SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "mainWindow creation success");
            
            SDL_SetWindowIcon(mainWindow, TheTextureManager::getInstance()->loadImgSurface("../Assets/Hibiki.ico"));

            renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_SOFTWARE);
            if(renderer != NULL) {
                SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "renderer creation success");
                //SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            } else {
                SDL_LogMessage(0, SDL_LOG_PRIORITY_ERROR, "renderer init fail");
                return false;
            }
        } else {
            SDL_LogMessage(0, SDL_LOG_PRIORITY_ERROR, "mainWindow init fail");
            return false;
        }
    } else {
        SDL_LogMessage(0, SDL_LOG_PRIORITY_ERROR, "SDL init fail");
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    TheGameObjectFactory::getInstance()->registerType("MenuButton", new MenuButtonCreator());	
	TheGameObjectFactory::getInstance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::getInstance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::getInstance()->registerType("StaticGameObject", new StaticGameObjectCreator());
	TheGameObjectFactory::getInstance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    
	gameStateMachine = new GameStateMachine();
	gameStateMachine->initialState();

    // load sprites -> gothloli2.png, officeman4.png -> 32x48
    /*if(!TheTextureManager::getInstance()->loadImg("../Assets/Characters/gothloli2.png", "gothloli2", renderer)){
        return false;
    }
    if(!TheTextureManager::getInstance()->loadImg("../Assets/Characters/officeman4.png", "officeman4", renderer)){
        return false;
    }*/
    //GameObject* player = TheGameObjectFactory::getInstance()->create("Player");
    //player->load(new LoaderParams(100, 100, 32, 48, "officeman4"));
    //gameObjects.push_back(player);
    //gameObjects.push_back(new Player(new LoaderParams(100, 100, 32, 48,"gothloli2")));
    //gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 32, 48,"officeman4")));
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Init success");  
    gameRunning = true; // everything inited successfully start the main loop
    return true;
}

void GameController::handleEvents() {
    TheInputManager::getInstance()->update();

    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_RETURN)) {
        gameStateMachine->changeState(HIBIKI_MAIN_MENU);
    }
}

void GameController::update() {
    gameStateMachine->update();
    //SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, std::to_string(currentFrame).c_str());
}

void GameController::render() {
    SDL_RenderClear(renderer); // clear the renderer to the draw color

    gameStateMachine->render();

    SDL_RenderPresent(renderer); // draw to the screen
}

void GameController::draw() {

}

void GameController::clean() {
    SDL_Log("cleaning GameController");
    TheInputManager::getInstance()->clean();
    TheTextureManager::getInstance()->clear();

    gameObjects.clear();
    gameRunning = false;

    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool GameController::isGameRunning() {
    return gameRunning;
}