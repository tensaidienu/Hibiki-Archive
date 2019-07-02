#include <iostream>
#include "zconf.h" 
#include "zlib.h"

#include "LevelParser.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"

#include "base64/base64.h"

using namespace std;

Level* LevelParser::parseLevel(const char *levelFile) {
    std::cout << "entering parseLevel\n";
    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    Level* level = new Level();

    // get the root node
    TiXmlElement* root = levelDocument.RootElement();

    root->Attribute("tilewidth", &tileSize);
    root->Attribute("width", &width);
    root->Attribute("height", &height);

    // parse the tilesets
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tileset")) {
            parseTilesets(root, e, level->getTilesets());
        }
    }
    // parse any object layers
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("layer")) {
            parseTileLayer(e, level->getLayers(), level->getTilesets());
        } else if(e->Value() == std::string("objectgroup")) {
            parseObjectLayer(e, level->getLayers());
        }
    }

    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (TiXmlElement* t = e->FirstChildElement(); t != NULL; t = t->NextSiblingElement()) {
                if (t->Value() == std::string("property")) {
                    TheTextureManager::getInstance()->loadImg(GlobalVariables::getInstance()->IMAGE_PATH + t->Attribute("value"), t->Attribute("name"), TheGame::getInstance()->getRenderer());
                    //parseTextures(t);
                }
            }
        }
    }
    // parse any object layers
    /*for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("layer")) {
            parseTileLayer(e, level->getLayers(), level->getTilesets());
        }
    }*/

    std::cout << "end parseLevel\n";
    return level;
}

void LevelParser::parseTilesets(TiXmlElement* root, TiXmlElement* tilesetRoot, std::vector<Tileset>* tilesets) {
    std::cout << "entering parseTilesets\n";
    TiXmlElement* imageRoot;
    // create a tileset object
    Tileset tileset;
    tilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    
    TiXmlDocument levelDocument;
    std::string tempString = "../Assets/SDL/";
    levelDocument.LoadFile(tempString + tilesetRoot->Attribute("source"));
    tilesetRoot = levelDocument.RootElement();    
    tileset.spacing = 0;
    tileset.margin = 0;

    std::string tempTransparency = "0";
    tilesetRoot->FirstChildElement()->QueryStringAttribute("trans", &tempTransparency);
    int imageTransparency = (int)strtol(tempTransparency.c_str(), NULL, 16);
    TheTextureManager::getInstance()->loadImg(GlobalVariables::getInstance()->IMAGE_PATH + tilesetRoot->FirstChildElement()->Attribute("source"), tilesetRoot->Attribute("name"), TheGame::getInstance()->getRenderer(), imageTransparency);

    tilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    tilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);    
    tilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    tilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    tilesetRoot->Attribute("spacing", &tileset.spacing);
    tilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = tilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    tilesets->push_back(tileset);
    std::cout << "end parseTilesets\n";
}

void LevelParser::parseTileLayer(TiXmlElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets) {
    //std::cout << "entering parseTileLayer\n";
    TileLayer* tileLayer = new TileLayer(tileSize, *tilesets);
    // tile data
    std::vector<std::vector<int>> data;
    std::string decodedIDs;
    TiXmlElement* dataNode;

    tileLayer->offsetX = 0;
    tileLayer->offsetY = 0;
    tileElement->Attribute("offsetx", &tileLayer->offsetX);
    tileElement->Attribute("offsety", &tileLayer->offsetY);

    for(TiXmlElement* e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("data")) {
            dataNode = e;
        }
    }
    for(TiXmlNode* e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    // uncompress zlib compression
    uLongf numGids = width * height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0], &numGids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    std::vector<int> layerRow(width);
    for(int j = 0; j < height; j++) {
        data.push_back(layerRow);
    }
    for(int rows = 0; rows < height; rows++) {
        for(int cols = 0; cols < width; cols++) {
            data[rows][cols] = gids[rows * width + cols];
        }
    }
    tileLayer->setTileIDs(data);
    layers->push_back(tileLayer);
}

void LevelParser::parseTextures(TiXmlElement* textureRoot) {
    TheTextureManager::getInstance()->loadImg(GlobalVariables::getInstance()->IMAGE_PATH + textureRoot->Attribute("value"), textureRoot->Attribute("name"), TheGame::getInstance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* objectElement, std::vector<Layer*> *layers) {
    ObjectLayer* objectLayer = new ObjectLayer();
    int x, y, width, height, numFrames, callbackID, animSpeed;
	std::string textureID;

	if (objectElement->FirstChildElement()->Value() == std::string("properties")) {		
        for (TiXmlElement* properties = objectElement->FirstChildElement()->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
			if (properties->Value() == std::string("property")) {                
				if (properties->Attribute("name") == std::string("numFrames")) {
				    properties->Attribute("value", &numFrames);
				} else if (properties->Attribute("name") == std::string("textureHeight")) {
					properties->Attribute("value", &height);
				} else if (properties->Attribute("name") == std::string("textureID")) {
					textureID = properties->Attribute("value");
				} else if (properties->Attribute("name") == std::string("textureWidth")) {
					properties->Attribute("value", &width);
				} else if (properties->Attribute("name") == std::string("callbackID")) {
					properties->Attribute("value", &callbackID);
				} else if (properties->Attribute("name") == std::string("animSpeed")) {
					properties->Attribute("value", &animSpeed);
				}
			}
		}
	}

    for (TiXmlElement* e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("object")) {
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			GameObject* gameObject = TheGameObjectFactory::getInstance()->create(e->Attribute("type"));
			gameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
			objectLayer->getGameObjects()->push_back(gameObject);
		}
	}
	layers->push_back(objectLayer);
}