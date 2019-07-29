#ifndef __Enemy_h__
#define __Enemy_h__

#include <iostream>

#include "SDL2/SDL.h"

#include "DynamicGameObject.h"
#include "../Factories/GameObjectFactory.h"
#include "../LoaderParams.h"

class Enemy : public DynamicGameObject {
    public:
        Enemy();
        ~Enemy(){};

        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update();
        virtual void clean();
};

class EnemyCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Enemy();
    }
};

#endif