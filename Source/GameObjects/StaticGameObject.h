#ifndef __StaticGameObject_h__
#define __StaticGameObject_h__

#include "GameObject.h"
#include "Collider.h"
#include "CollisionGameObject.h"
#include "../Vector2D.h"
#include "../Factories/GameObjectFactory.h"

class StaticGameObject : public CollisionGameObject {
    protected:
        int currentRow;
        int currentFrame;
        int numFrames;
        std::string gameObjectID;
        std::string type;
    public:
        StaticGameObject();
        ~StaticGameObject(){};

        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update(); 
        virtual void clear();

        Vector2D& getPosition() { return position; }
        Vector2D& getVelocity() { return velocity; }
        Vector2D& getAcceleration() { return acceleration; }
        Collider& getCollider() { return collider; }
        int getWidth() { return width; }
        int getHeight() { return height; }
        std::string getID() { return gameObjectID; }
        void setFuncCallback(std::function<void()> func);
	    std::string getCallbackID() { return this->callbackID; }
};

class StaticGameObjectCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new StaticGameObject();
    }
};

#endif