#ifndef __GameObjectFactory_h__
#define __GameObjectFactory_h__

#include <string>
#include <map>

#include "SDL2/SDL.h"

#include "../GameObjects/GameObject.h"

class BaseCreator {
    public:
        virtual GameObject* createGameObject() const = 0;
        virtual ~BaseCreator(){}
};

class GameObjectFactory {
     private:
        GameObjectFactory(){}
        ~GameObjectFactory(){}

        static GameObjectFactory* gameObjectFactory;

        std::map<std::string, BaseCreator*> creators;
    public:
        static GameObjectFactory* getInstance() {
            if(gameObjectFactory == 0) {
                gameObjectFactory = new GameObjectFactory();
                return gameObjectFactory;
            }
            return gameObjectFactory;
        }
        bool registerType(std::string typeID, BaseCreator* creator) {
            std::map<std::string, BaseCreator*>::iterator it = this->creators.find(typeID);
            // if the type is already registered, do nothing
            if(it != this->creators.end()) {
                delete creator;
                return false;
            }
            this->creators[typeID] = creator;
            return true;
        }
        GameObject* create(std::string typeID) {
            std::map<std::string, BaseCreator*>::iterator it = this->creators.find(typeID);
            if(it == this->creators.end()) {
                SDL_Log("Could not find type: %s", typeID.c_str());
                return nullptr;
            }
            SDL_Log("Create: %s", typeID.c_str());
            BaseCreator* creator = (*it).second;
            return creator->createGameObject();            
        }
};

typedef GameObjectFactory TheGameObjectFactory;

#endif