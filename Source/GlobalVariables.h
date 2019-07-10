#ifndef __GlobalVariables_h__
#define __GlobalVariables_h__

#include <iostream>
#include <string>
#include <algorithm>

typedef enum {
    HIBIKI_MAIN_MENU = 1,
    HIBIKI_PLAY,
    HIBIKI_PAUSE,
    HIBIKI_GAME_OVER
} Hibiki_GameState;

const std::string WHITESPACE = " \n\r\t\f\v";
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
};

typedef GlobalVariables TheGlobalVariables;

#endif