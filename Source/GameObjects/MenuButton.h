#ifndef __MenuButton_h__
#define __MenuButton_h__

#include "SDLGameObject.h"
#include "../Factories/GameObjectFactory.h"
#include "../LoaderParams.h"

class MenuButton : public SDLGameObject {
    private:
        enum button_state {
		    MOUSE_OUT = 0,
		    MOUSE_OVER = 1,
		    CLICKED = 2
	    };
	    void (*callback) ();
        //void (*onClickEvent) ();
	    int callbackID;
        bool released;
    public:
        MenuButton();
        ~MenuButton();
        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update();
        virtual void clean();
	    void setCallback(void(*callback)()) { this->callback = callback; }
	    int getCallbackID() { return this->callbackID; }
};

class MenuButtonCreator : public BaseCreator {
    public:
	    GameObject* createGameObject() const {
		    return new MenuButton();
	    }
};

#endif