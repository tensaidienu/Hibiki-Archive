#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "PlayState.h"
//#include "MainMenuState.h"
//#include "MenuButton.h"
//#include "AnimatedGraphic.h"

using namespace std;

Game* Game::gameInstance = 0;

/*
Game::Game() {
   mainWindow   = NULL;
   renderer = NULL;
   gameRunning  = true;
}

Game::~Game() {

}
*/

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    //flags = SDL_WINDOW_RESIZABLE;
    flags = SDL_WINDOW_SHOWN;
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
    
    TheInputHandler::getInstance()->initialiseJoysticks();

    /*TheGameObjectFactory::getInstance()->registerType("MenuButton", new MenuButtonCreator());	
	TheGameObjectFactory::getInstance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::getInstance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::getInstance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    */
	//gameStateMachine = new GameStateMachine();
	//gameStateMachine->changeState(new MainMenuState());

    // load sprites -> gothloli2.png, officeman4.png -> 32x48
    if(!TheTextureManager::getInstance()->loadImg("../Assets/Characters/gothloli2.png", "gothloli2", renderer)){
        return false;
    }
    if(!TheTextureManager::getInstance()->loadImg("../Assets/Characters/officeman4.png", "officeman4", renderer)){
        return false;
    }

    //gameObjects.push_back(new Player(new LoaderParams(100, 100, 32, 48,"country-platform-back")));
    //gameObjects.push_back(new Player(new LoaderParams(100, 100, 32, 48,"gothloli2")));
    //gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 32, 48,"officeman4")));
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Init success");  
    gameRunning = true; // everything inited successfully start the main loop
    return true;
}

void Game::handleEvents() {
    TheInputHandler::getInstance()->update();

    //if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RETURN)) {
      //  gameStateMachine->changeState(new PlayState());
    //}
}

void Game::update() {
    //gameStateMachine->update();
    /*
    for(std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++) {
        gameObjects[i]->update();
    }*/
    //SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, std::to_string(currentFrame).c_str());  
}

void Game::render() {
    SDL_RenderClear(renderer); // clear the renderer to the draw color
    
    TheTextureManager::getInstance()->drawFrame("gothloli2", 100, 100, 32, 48, 1, currentFrame, renderer);
    TheTextureManager::getInstance()->drawFrame("gothloli2", 150, 150, 32, 48, 1, currentFrame, renderer);
    //Game::draw();

    //gameStateMachine->render();

    SDL_RenderPresent(renderer); // draw to the screen
}

void Game::draw() {
    /*for(std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++) {
        gameObjects[i]->draw();
    }*/
}

void Game::clean() {
    SDL_Log("cleaning game");

    TheInputHandler::getInstance()->clean();

    gameRunning = false;

    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::isGameRunning() {
    return gameRunning;
}