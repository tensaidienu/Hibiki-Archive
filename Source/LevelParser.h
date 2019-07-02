#ifndef __LevelParser_h__
#define __LevelParser_h__

#include <vector>

#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "GlobalVariables.h"

#include "tinyXml/tinyxml.h"

class LevelParser {
     private:        
        void parseTilesets(TiXmlElement* root, TiXmlElement* tilesetRoot, std::vector<Tileset>* tilesets);
        void parseTileLayer(TiXmlElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets);
        void parseTextures(TiXmlElement* textureRoot);
        void parseObjectLayer(TiXmlElement* objectElement, std::vector<Layer*> *layers);
        int tileSize;
        int width;
        int height;
    public:
        Level* parseLevel(const char* levelFile);
};

#endif