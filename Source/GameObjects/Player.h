#ifndef __Player_h__
#define __Player_h__

#include <iostream>

#include "SDL2/SDL.h"

#include "DynamicGameObject.h"
#include "../Factories/GameObjectFactory.h"

class Player : public DynamicGameObject {
    private:
        void handleInput();
    public:
        Player();
        ~Player(){};
        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update();
        virtual void clear();
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif