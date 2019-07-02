#ifndef __ObjectLayer_h__
#define __ObjectLayer_h__

#include <vector>

#include "Layer.h"
#include "../GameObjects/GameObject.h"

class ObjectLayer : public Layer {
    public:
        virtual void update();
        virtual void render();
        std::vector<GameObject*>* getGameObjects() {
            return &gameObjects;
        }
    private:
        std::vector<GameObject*> gameObjects;
};

#endif