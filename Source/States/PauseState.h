#ifndef __PauseState_h__
#define __PauseState_h__

#include <vector>

#include "MenuState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/MenuButton.h"

class PauseState : public MenuState {
    private:
        static void pauseToMain();
        static void resumePlay(); 
        
        static const std::string pauseID;
        std::vector<GameObject*> gameObjects;

        virtual void setCallbacks();
    public:
        PauseState();
        ~PauseState();
        
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return pauseID; }        
};

#endif