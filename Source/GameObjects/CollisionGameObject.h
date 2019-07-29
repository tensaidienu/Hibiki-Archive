#ifndef __CollisionGameObject_h__
#define __CollisionGameObject_h__

#include <functional>

#include "GameObject.h"
#include "Collider.h"
#include "../Vector2D.h"

class CollisionGameObject : public GameObject {
    protected:        
        int width;
        int height;

        Vector2D position;
        Vector2D velocity;
        Vector2D acceleration;
        Collider collider;
        std::string callbackID;
        std::function<void()> functionCallback;
    public:
        CollisionGameObject();
        ~CollisionGameObject(){};

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
        void setFuncCallback(std::function<void()> func);
	    std::string getCallbackID() { return this->callbackID; }
};

#endif