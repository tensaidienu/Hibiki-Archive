#ifndef __GameState_h__
#define __GameState_h__

#include <iostream>
#include <string>

class GameState {
    protected:
        std::vector<std::string> textureIDList;
    public:
        virtual ~GameState() { std::cout << "Destructor of GameState" << std::endl; }
        virtual void update() = 0;
        virtual void render() = 0;
        virtual bool onEnter() = 0;
        virtual bool onExit() = 0;
        virtual std::string getStateID() const = 0;
};

#endif