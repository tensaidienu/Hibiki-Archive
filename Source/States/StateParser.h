#ifndef __StateParser_h__
#define __StateParser_h__

#include <iostream>
#include <vector>

#include "../Libs/tinyXml/tinyxml2.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class GameObject;

class StateParser {
    public:
	    bool parseState(std::string stateFile, std::string stateID, std::vector<GameObject*> *objects, std::vector<std::string> *textureIDs);
    private:
	    void parseObjects(XMLElement* stateRoot, std::vector<GameObject*> *objects);
	    void parseTextures(XMLElement* stateRoot, std::vector<std::string> *textureIDs);
};

#endif