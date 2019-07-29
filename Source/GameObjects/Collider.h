#ifndef __Collider_h__
#define __Collider_h__

#include "../GlobalVariables.h"
#include "GameObject.h"
#include "../Vector2D.h"

class Collider {
    protected:
        Vector2D offset;
        Vector2D size;
        Vector2D gravity;
        HibikiCollisionType type;
    public:
        Collider();
        ~Collider();

        virtual void load(float x, float y, std::string type);
        virtual void draw(int width, int height);
        virtual void update(); 
        virtual void clean();

        Vector2D& getOffset() { return offset; }
        Vector2D& getSize() { return size; }
        Vector2D& getGravity() { return gravity; }
        HibikiCollisionType& getType() { return type; }
};

#endif