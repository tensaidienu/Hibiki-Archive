#ifndef __LevelParser_h__
#define __LevelParser_h__

#include <vector>

#include "SDL2/SDL.h"

#include "Level.h"
#include "../Managers/TextureManager.h"
#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Libs/tinyXml/tinyxml2.h"

using namespace tinyxml2;

/*#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { SDL_Log("Error: %i", a_eResult.c_str()); return a_eResult; }
#endif*/

class LevelParser {
     private:        
        void parseTilesets(XMLElement* root, XMLElement* tilesetRoot, std::vector<Tileset>* tilesets);
        void parseTileLayer(XMLElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets);
        void parseObjects(XMLElement* objectElement, std::vector<Layer*> *layers, std::string name, Level* level);
        
        void parseEnemies(XMLElement* objectElement, std::vector<Layer*> *layers, Level* level);
        void parseStaticGameObjects(XMLElement* objectElement, std::vector<Layer*> *layers, Level* level);
        void parsePlayers(XMLElement* objectElement, std::vector<Layer*> *layers, Level* level);
        
        int tileSize = 0;
        int width = 0;
        int height = 0;
    public:
        Level* parseLevel(std::string levelFile);
};

#endif