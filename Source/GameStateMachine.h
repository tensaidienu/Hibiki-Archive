#ifndef __GameStateMachine_h__
#define __GameStateMachine_h__

#include <vector>

#include "GameState.h"

class GameStateMachine {
    private:
        std::vector<GameState*> gameStates;
    public:
        void pushState(GameState* state);
        void changeState(GameState* state);
        void popState();
        void update();
        void render();
};

#endif