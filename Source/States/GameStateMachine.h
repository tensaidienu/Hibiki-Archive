#ifndef __GameStateMachine_h__
#define __GameStateMachine_h__

#include <vector>

#include "../GlobalVariables.h"

#include "GameState.h"

class GameStateMachine {
    private:
        GameState* gameState;
        GameState* tempGameState;
        bool wait = false;
    public:
        GameStateMachine();
        ~GameStateMachine();
        void initialState();
        void changeState(HibikiGameState type);
        void pauseToMain();
        void resumePlay();
        void update();
        void render();
};

#endif