#ifndef __Game_h__
#define __Game_h__

#include <vector>

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "GameStateMachine.h"

class Game {
    private:
        Game(){}
        ~Game(){}

        static Game* gameInstance;

        SDL_Window* mainWindow;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        std::vector<GameObject*> gameObjects;

        int gameWidth;
	    int gameHeight;
        int currentFrame;
        bool gameRunning;

        GameStateMachine* gameStateMachine;
    public:
        static Game* getInstance() {
            if(gameInstance == 0) {
                gameInstance = new Game();
                return gameInstance;
            }
            return gameInstance;
        }
        bool init(const char* title, int xpos, int ypos, int width, int height, int tags);
        void handleEvents();
        void update();
        void render();
        void draw();
        void clean();
        bool isGameRunning();
        SDL_Renderer* getRenderer() const { return renderer; }
        GameStateMachine* getStateMachine() { return gameStateMachine; }
        int getGameWidth() const { return gameWidth; }
        int getGameHeight() const { return gameHeight; }
};

typedef Game TheGame;

#endif