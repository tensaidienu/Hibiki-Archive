#ifndef __PlayState_h__
#define __PlayState_h__

#include <vector>

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/DynamicGameObject.h"
#include "../GameObjects/StaticGameObject.h"
#include "../Levels/Level.h"

class PlayState : public GameState {
    private:
        static const std::string playID;
        Level* level;
    public:
        PlayState();
        ~PlayState();
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return playID; };
};

#endif