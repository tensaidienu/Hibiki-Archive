#ifndef __GlobalVariables_h__
#define __GlobalVariables_h__

#include <iostream>

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
        int getTest() const { return 555; }
        std::string ASSETS_PATH = "../Assets/";
        std::string MAP_PATH = "../Assets/SDL/";
        std::string IMAGE_PATH = "../Assets/Map/";
};

typedef GlobalVariables TheGlobalVariables;

#endif