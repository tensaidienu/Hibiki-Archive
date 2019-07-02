#ifndef __MainMenuState_h__
#define __MainMenuState_h__

#include <vector>

#include "../GameObjects/GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState {
    private:
        static void menuToPlay();
        static void exitFromMenu();

        static const std::string menuID;
        std::vector<GameObject*> gameObjects;  

        virtual void setCallbacks(const std::vector<Callback>& callbacks);
    public:
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return menuID; }
};

#endif