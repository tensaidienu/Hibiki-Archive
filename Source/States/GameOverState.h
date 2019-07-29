#ifndef __GameOverState_h__
#define __GameOverState_h__

#include <vector>

#include "MenuState.h"
#include "../GameObjects/GameObject.h"

class GameOverState : public MenuState {
    private:
	    static void gameOverToMain();
	    static void restartPlay();

	    static const std::string gameOverID;
	    std::vector<GameObject*> gameObjects;

		 virtual void setCallbacks();
    public:
	    virtual void update();
	    virtual void render();

	    virtual bool onEnter();
	    virtual bool onExit();
	   
	    virtual std::string getStateID() const { return gameOverID; }
};

#endif