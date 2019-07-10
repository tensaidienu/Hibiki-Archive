#ifndef __GlobalVariables_h__
#define __GlobalVariables_h__

#include <iostream>

typedef enum {
    HIBIKI_MAIN_MENU = 1,
    HIBIKI_PLAY,
    HIBIKI_PAUSE,
    HIBIKI_GAME_OVER
} Hibiki_GameState;

static const std::string PATH_ASSETS = "../Assets/";
static const std::string PATH_MAPS = "../Assets/Maps/";
static const std::string PATH_TILESETS = "../Assets/Maps/Tilesets/";
static const std::string PATH_TSX = "../Assets/Maps/TSX/";
static const std::string PATH_CHARACTERS = "../Assets/Characters/";
static const std::string PATH_GUI = "../Assets/GUI/";
static const std::string PATH_MENU = "../Assets/GUI/Menu/";

class GlobalVariables {
    private:
        GlobalVariables(){}
        ~GlobalVariables(){}

        static GlobalVariables* globalVariablesInstance;
    public:
        static GlobalVariables* getInstance() {
            if(globalVariablesInstance == 0) {
                globalVariablesInstance = new GlobalVariables();
                return globalVariablesInstance;
            }
            return globalVariablesInstance;
        }        
        
        
};

typedef GlobalVariables TheGlobalVariables;

#endif