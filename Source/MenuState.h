#ifndef __MenuState_h__
#define __MenuState_h__

#include "GameState.h"

class MenuState : public GameState {
    protected:
	    typedef void(*Callback)();
	    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	    std::vector<Callback> callbacks;
};

#endif