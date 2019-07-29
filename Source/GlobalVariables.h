#ifndef __GlobalVariables_h__
#define __GlobalVariables_h__

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

typedef enum {
    HIBIKI_MAIN_MENU = 1,
    HIBIKI_PLAY,
    HIBIKI_PAUSE,
    HIBIKI_GAME_OVER
} HibikiGameState;

typedef enum {
    COLLISION_BLOCK = 1,
    COLLISION_TRIGGER,
    COLLISION_BLOCK_AND_TRIGGER,
    CLICK_TRIGGER,
    COLLISION_BLOCK_CLICK_TRIGGER
} HibikiCollisionType;

const std::string WHITESPACE = " \n\r\t\f\v";
static const std::string PATH_ASSETS = "../Assets/";
static const std::string PATH_MAPS = "../Assets/Maps/";
static const std::string PATH_TILESETS = "../Assets/Maps/Tilesets/";
static const std::string PATH_TSX = "../Assets/Maps/TSX/";
static const std::string PATH_CHARACTERS = "../Assets/Characters/";
static const std::string PATH_GUI = "../Assets/GUI/";
static const std::string PATH_MENU = "../Assets/GUI/Menu/";

static std::map<std::string, HibikiCollisionType> hibikiCollisionTypeMap;

class GlobalVariables {
    private:
        GlobalVariables(){
            hibikiCollisionTypeMap["COLLISION_BLOCK"] = COLLISION_BLOCK;
            hibikiCollisionTypeMap["COLLISION_TRIGGER"] = COLLISION_TRIGGER;
            hibikiCollisionTypeMap["COLLISION_BLOCK_AND_TRIGGER"] = COLLISION_BLOCK_AND_TRIGGER;
            hibikiCollisionTypeMap["CLICK_TRIGGER"] = CLICK_TRIGGER;
            hibikiCollisionTypeMap["COLLISION_BLOCK_CLICK_TRIGGER"] = COLLISION_BLOCK_CLICK_TRIGGER;
         }
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

        static std::string ltrim(const std::string& s) {
	        size_t start = s.find_first_not_of(WHITESPACE);
	        return (start == std::string::npos) ? "" : s.substr(start);
        }

        static std::string rtrim(const std::string& s) {
	        size_t end = s.find_last_not_of(WHITESPACE);
	        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
        }

        static std::string trim(const std::string& s) {
	        return rtrim(ltrim(s));
        }
        
        static HibikiCollisionType getCollisionTypeByString(std::string type) {
            return hibikiCollisionTypeMap[type];
        }
};

typedef GlobalVariables TheGlobalVariables;

#endif