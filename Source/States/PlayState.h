#ifndef __PlayState_h__
#define __PlayState_h__

#include <vector>

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/SDLGameObject.h"
#include "../Levels/Level.h"

class PlayState : public GameState {
    private:
        bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

        static const std::string playID;
        Level* level;
        std::vector<GameObject*> gameObjects;
    public:
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return playID; };        
};

#endif