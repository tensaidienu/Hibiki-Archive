#ifndef __Player_h__
#define __Player_h__

#include <iostream>

#include "SDL2/SDL.h"

#include "SDLGameObject.h"
#include "../Factories/GameObjectFactory.h"
#include "../LoaderParams.h"

class Player : public SDLGameObject {
    private:
        void handleInput();
    public:
        Player();
        ~Player(){};
        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update();
        virtual void clean();
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif