#ifndef __AnimatedGraphic_h__
#define __AnimatedGraphic_h__

#include "SDLGameObject.h"
#include "../Factories/GameObjectFactory.h"
#include "../LoaderParams.h"

class AnimatedGraphic : public SDLGameObject {
    private:
	    int animSpeed;
    public:
        AnimatedGraphic();
	    ~AnimatedGraphic(){};

		virtual void load(const LoaderParams* params);
		virtual void draw();
	    virtual void update();
	    virtual void clean();
};

class AnimatedGraphicCreator : public BaseCreator {
    public:
	    GameObject* createGameObject() const {
		    return new AnimatedGraphic();
	    }
};

#endif