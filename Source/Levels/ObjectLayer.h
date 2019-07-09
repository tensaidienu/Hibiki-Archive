#ifndef __ObjectLayer_h__
#define __ObjectLayer_h__

#include <vector>

#include "Layer.h"
#include "../GameObjects/GameObject.h"

class ObjectLayer : public Layer {
    private:
        std::vector<GameObject*> gameObjects;
    public:
        ObjectLayer();
        ~ObjectLayer();
        virtual void update();
        virtual void render();
        std::vector<GameObject*>* getGameObjects() {
            return &gameObjects;
        }    
};

#endif