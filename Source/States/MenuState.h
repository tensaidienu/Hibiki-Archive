#ifndef __MenuState_h__
#define __MenuState_h__

#include <functional>
#include <map>
#include <vector>

#include "GameState.h"

class MenuState : public GameState {
    protected:
		std::map<std::string, std::function<void()>> functionCallbacks;
};

#endif