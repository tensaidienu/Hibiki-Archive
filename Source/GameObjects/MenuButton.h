#ifndef __MenuButton_h__
#define __MenuButton_h__

#include <functional>

#include "DynamicGameObject.h"
#include "../Factories/GameObjectFactory.h"
#include "../LoaderParams.h"

class MenuButton : public DynamicGameObject {
    private:
        enum button_state {
		    MOUSE_OUT = 0,
		    MOUSE_OVER = 1,
		    CLICKED = 2
	    };
        bool released = true;
    public:
        MenuButton();
        ~MenuButton();
        virtual void load(const LoaderParams* params);
        virtual void draw();
        virtual void update();
        virtual void clear();
        void setFuncCallback(std::function<void()> func);
	    std::string getCallbackID() { return this->callbackID; }
};

class MenuButtonCreator : public BaseCreator {
    public:
	    GameObject* createGameObject() const {
		    return new MenuButton();
	    }
};

#endif