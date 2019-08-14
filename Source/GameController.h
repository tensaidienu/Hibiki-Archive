#ifndef __Game_h__
#define __Game_h__

#include <vector>

#include "SDL2/SDL.h"

#include "GameObjects/GameObject.h"
#include "States/GameStateMachine.h"

class GameController {
    private:
        GameController();
        ~GameController();

        static GameController* gameInstance;

        SDL_Window* mainWindow = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

        int gameWidth;
	    int gameHeight;
        int currentFrame;
        bool gameRunning  = true;

        GameStateMachine* gameStateMachine = nullptr;
    public:
        static GameController* getInstance() {
            if(gameInstance == 0) {
                gameInstance = new GameController();
                return gameInstance;
            }
            return gameInstance;
        }
        bool init(std::string title, int xpos, int ypos, int width, int height, int tags);
        void handleEvents();
        void update();
        void render();
        void draw();
        void clear();
        bool isGameRunning();
        void setGameRunning(bool gameRunning);
        SDL_Renderer* getRenderer() const { return renderer; }
        GameStateMachine* getStateMachine() { return gameStateMachine; }
        int getGameWidth() const { return gameWidth; }
        int getGameHeight() const { return gameHeight; }
};

typedef GameController TheGame;

#endif