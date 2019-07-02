#ifndef __SDLGameObject_h__
#define __SDLGameObject_h__

#include "GameObject.h"
#include "../Vector2D.h"

class SDLGameObject : public GameObject {
    protected:        
        int width;
        int height;
        int currentRow;
        int currentFrame;
        int numFrames;
        std::string textureID;

        Vector2D position;
        Vector2D velocity;
        Vector2D acceleration;
    public:
        SDLGameObject();

        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update(); 
        virtual void clean();

        Vector2D& getPosition() { return position; }
        int getWidth() { return width; }
        int getHeight() { return height; }
};

#endif