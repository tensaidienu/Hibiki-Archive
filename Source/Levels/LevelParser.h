#ifndef __LevelParser_h__
#define __LevelParser_h__

#include <vector>

#include "Level.h"
#include "../Managers/TextureManager.h"
#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Libs/tinyXml/tinyxml2.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class LevelParser {
     private:        
        void parseTilesets(XMLElement* root, XMLElement* tilesetRoot, std::vector<Tileset>* tilesets);
        void parseTileLayer(XMLElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets);
        void parseObjectLayer(XMLElement* objectElement, std::vector<Layer*> *layers);
        int tileSize;
        int width;
        int height;
    public:
        Level* parseLevel(std::string levelFile);
};

#endif