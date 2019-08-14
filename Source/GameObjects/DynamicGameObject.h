#ifndef __DynamicGameObject_h__
#define __DynamicGameObject_h__

#include "GameObject.h"
#include "Collider.h"
#include "CollisionGameObject.h"
#include "../Vector2D.h"

class DynamicGameObject : public CollisionGameObject {
    protected:
        int currentRow = 0;
        int currentFrame = 0;
        int numFrames = 0;
        int direction = 0;
        std::string textureID = "";
    public:
        DynamicGameObject();
        ~DynamicGameObject(){};

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
        int getDirection() { return direction = 0; }
        void setDirection(int direction2) { direction = direction2; }
        void setFuncCallback(std::function<void()> func);
	    std::string getCallbackID() { return this->callbackID; }
};

#endif