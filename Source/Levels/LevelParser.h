#ifndef __LevelParser_h__
#define __LevelParser_h__

#include <vector>

#include "Level.h"
#include "../Managers/TextureManager.h"
#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Libs/tinyXml/tinyxml.h"

class LevelParser {
     private:        
        void parseTilesets(TiXmlElement* root, TiXmlElement* tilesetRoot, std::vector<Tileset>* tilesets);
        void parseTileLayer(TiXmlElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets);
        void parseObjectLayer(TiXmlElement* objectElement, std::vector<Layer*> *layers);
        int tileSize;
        int width;
        int height;
    public:
        Level* parseLevel(std::string levelFile);
};

#endif