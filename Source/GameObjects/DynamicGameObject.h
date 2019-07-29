#ifndef __DynamicGameObject_h__
#define __DynamicGameObject_h__

#include "GameObject.h"
#include "Collider.h"
#include "CollisionGameObject.h"
#include "../Vector2D.h"

class DynamicGameObject : public CollisionGameObject {
    protected:
        int currentRow;
        int currentFrame;
        int numFrames;
        int direction;
        std::string textureID;
    public:
        DynamicGameObject();
        ~DynamicGameObject(){};

        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update(); 
        virtual void clean();

        Vector2D& getPosition() { return position; }
        Vector2D& getVelocity() { return velocity; }
        Vector2D& getAcceleration() { return acceleration; }
        Collider& getCollider() { return collider; }
        int getWidth() { return width; }
        int getHeight() { return height; }
        int getDirection() { return direction; }
        void setDirection(int direction2) { direction = direction2; }
        void setFuncCallback(std::function<void()> func);
	    std::string getCallbackID() { return this->callbackID; }
};

#endif