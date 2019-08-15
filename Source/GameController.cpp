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
    
}

GameController::~GameController() {

}

bool GameController::init(std::string title, int xpos, int ypos, int width, int height, int flags) {
    //flags = SDL_WINDOW_RESIZABLE;
    //flags = SDL_WINDOW_SHOWN;
	this->gameWidth = width;
	this->gameHeight = height;

    // attempt to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) == 0) {
    //if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "SDL init success");
        
        this->mainWindow = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
        if(this->mainWindow != nullptr) {
            SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "mainWindow creation success");
            
            SDL_SetWindowIcon(this->mainWindow, TheTextureManager::getInstance()->loadImgSurface("../Assets/Hibiki.ico"));

            this->renderer = SDL_CreateRenderer(this->mainWindow, -1, SDL_RENDERER_SOFTWARE);
            if(this->renderer != nullptr) {
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

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

    TheGameObjectFactory::getInstance()->registerType("MenuButton", new MenuButtonCreator());	
	TheGameObjectFactory::getInstance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::getInstance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::getInstance()->registerType("StaticGameObject", new StaticGameObjectCreator());
	TheGameObjectFactory::getInstance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    
	this->gameStateMachine = new GameStateMachine();
	this->gameStateMachine->initialState();

    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Init success");  
    this->gameRunning = true; // everything inited successfully start the main loop
    return true;
}

void GameController::handleEvents() {
    TheInputManager::getInstance()->update();

    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_RETURN) && this->gameStateMachine) {
        this->gameStateMachine->changeState(HIBIKI_MAIN_MENU);
    }
}

void GameController::update() {
    if (this->gameStateMachine) {
        this->gameStateMachine->update();
    }
}

void GameController::render() {
    SDL_RenderClear(this->renderer); // clear the renderer to the draw color

    if (this->gameStateMachine) {
        this->gameStateMachine->render();
    }

    SDL_RenderPresent(this->renderer); // draw to the screen
}

void GameController::draw() {

}

void GameController::clear() {
    SDL_Log("Cleaning GameController");

    this->gameRunning = false;

    delete this->gameStateMachine;
    this->gameStateMachine = nullptr;

    TheInputManager::getInstance()->clear();
    TheTextureManager::getInstance()->clear();

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    this->texture = nullptr;
    this->renderer = nullptr;
    this->mainWindow = nullptr;

    SDL_Quit();
}

bool GameController::isGameRunning() {
    return this->gameRunning;
}

void GameController::setGameRunning(bool gameRunning) {
    this->gameRunning = gameRunning;
}