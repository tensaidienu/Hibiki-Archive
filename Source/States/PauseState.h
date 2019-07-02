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
    public:
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return pauseID; }
        virtual void setCallbacks(const std::vector<Callback> &callbacks);
};

#endif