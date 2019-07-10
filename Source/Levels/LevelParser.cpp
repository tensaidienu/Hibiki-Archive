#include <iostream>
#include "zconf.h" 
#include "zlib.h"

#include "LevelParser.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "../Factories/GameObjectFactory.h"

#include "../Libs/base64/base64.h"

Level* LevelParser::parseLevel(std::string levelFile) {
    //std::cout << "entering parseLevel\n";
    // create a TinyXML document and load the map XML
    XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile.c_str());
    Level* level = new Level();

    // get the root node
    XMLElement* root = levelDocument.RootElement();

    if(root->FirstChildElement() == nullptr){
        return nullptr;
    }

    root->QueryIntAttribute("tilewidth", &tileSize);
    root->QueryIntAttribute("width", &width);
    root->QueryIntAttribute("height", &height);

    

    // parse the tilesets
    for(XMLElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tileset")) {
            parseTilesets(root, e, level->getTilesets());

        }
    }

    //parse the textures
    std::string tempTransparency = "0", tempPath = "0", tempName = "0";    
    for (XMLElement* t = root->FirstChildElement(); t != NULL; t = t->NextSiblingElement()) {
        if (t->Value() == std::string("group")) {
            t = t->FirstChildElement();
            if (t->Value() == std::string("objectgroup")) {
                for (XMLElement* object = t->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
                    if (object->Value() == std::string("object")) {
                        tempName = object->Attribute("name");
                        object = object->FirstChildElement();
                        if (object->Value() == std::string("properties")) {
                            for (XMLElement* property = object->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
                                if (property->Value() == std::string("property")) {
                                    if (property->Attribute("name") == std::string("Path")) {
                                        tempPath = property->Attribute("value");
                                    }
                                    if (property->Attribute("name") == std::string("Transparency")) {
                                        tempTransparency = property->Attribute("value");
                                    }                                    
                                }                                
                            }
                        }
                        TheTextureManager::getInstance()->loadImg(PATH_CHARACTERS + tempPath, tempName, TheGame::getInstance()->getRenderer(), tempTransparency);
                    }
                }
            }
        }
    }

    // parse any object layers
    for(XMLElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("layer")) {
            parseTileLayer(e, level->getLayers(), level->getTilesets());
        } else if(e->Value() == std::string("objectgroup")) {
            parseObjectLayer(e, level->getLayers());
        }
    }

    //std::cout << "end parseLevel\n";
    return level;
}

void LevelParser::parseTilesets(XMLElement* root, XMLElement* tilesetRoot, std::vector<Tileset>* tilesets) {
    //std::cout << "entering parseTilesets\n";
    XMLElement* imageRoot;
    // create a tileset object
    Tileset tileset;
    
    tilesetRoot->QueryIntAttribute("firstgid", &tileset.firstGridID);

    
    
    XMLDocument levelDocument;
    //std::string kuso = PATH_MAPS + tilesetRoot->Attribute("source");
    //const char *cstr = kuso.c_str();
    levelDocument.LoadFile((PATH_MAPS + tilesetRoot->Attribute("source")).c_str());
    tilesetRoot = levelDocument.RootElement();
    tileset.spacing = 0;
    tileset.margin = 0;

    if(tilesetRoot->FirstChildElement() == nullptr){
        return;
    }

    const char* kuso = "0";
    tilesetRoot->FirstChildElement()->QueryStringAttribute("trans", &kuso);
    std::string tempTransparency(kuso);    
    TheTextureManager::getInstance()->loadImg(PATH_TILESETS + tilesetRoot->FirstChildElement()->Attribute("source"), tilesetRoot->Attribute("name"), TheGame::getInstance()->getRenderer(), tempTransparency);

    tilesetRoot->FirstChildElement()->QueryIntAttribute("width", &tileset.width);
    tilesetRoot->FirstChildElement()->QueryIntAttribute("height", &tileset.height);    
    tilesetRoot->QueryIntAttribute("tilewidth", &tileset.tileWidth);
    tilesetRoot->QueryIntAttribute("tileheight", &tileset.tileHeight);
    tilesetRoot->QueryIntAttribute("spacing", &tileset.spacing);
    tilesetRoot->QueryIntAttribute("margin", &tileset.margin);
    tileset.name = tilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    tilesets->push_back(tileset);
    //std::cout << "end parseTilesets\n";
}

void LevelParser::parseTileLayer(XMLElement* tileElement, std::vector<Layer*> *layers, const std::vector<Tileset>* tilesets) {
    if(tileElement->FirstChildElement() == nullptr){
        return;
    }

    //std::cout << "XXXXXXXXXXXXXXXXXXXXXX" << std::endl;
    //std::cout << "YYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;

    TileLayer* tileLayer = new TileLayer(tileSize, *tilesets);
    // tile data
    std::vector<std::vector<int>> data;
    std::string decodedIDs;
    XMLElement* dataNode;

    tileLayer->offsetX = 0;
    tileLayer->offsetY = 0;
    tileElement->QueryIntAttribute("offsetx", &tileLayer->offsetX);
    tileElement->QueryIntAttribute("offsety", &tileLayer->offsetY);

    for(XMLElement* e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("data")) {
            dataNode = e;
        }
    }
    //NODE
    for(XMLNode* e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        XMLText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(TheGlobalVariables::trim(t));
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

void LevelParser::parseObjectLayer(XMLElement* objectElement, std::vector<Layer*> *layers) {
    if(objectElement->FirstChildElement() == nullptr){
        return;
    }

    ObjectLayer* objectLayer = new ObjectLayer();
    int x, y, width, height, numFrames, callbackID, animSpeed;
	std::string textureID;

	if (objectElement->FirstChildElement()->Value() == std::string("properties")) {		
        for (XMLElement* properties = objectElement->FirstChildElement()->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
			if (properties->Value() == std::string("property")) {                
				if (properties->Attribute("name") == std::string("numFrames")) {
				    properties->QueryIntAttribute("value", &numFrames);
				} else if (properties->Attribute("name") == std::string("textureHeight")) {
					properties->QueryIntAttribute("value", &height);
				} else if (properties->Attribute("name") == std::string("textureID")) {
					textureID = properties->Attribute("value");
				} else if (properties->Attribute("name") == std::string("textureWidth")) {
					properties->QueryIntAttribute("value", &width);
				} else if (properties->Attribute("name") == std::string("callbackID")) {
					properties->QueryIntAttribute("value", &callbackID);
				} else if (properties->Attribute("name") == std::string("animSpeed")) {
					properties->QueryIntAttribute("value", &animSpeed);
				}
			}
		}
	}

    for (XMLElement* e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("object")) {
			e->QueryIntAttribute("x", &x);
			e->QueryIntAttribute("y", &y);
			GameObject* gameObject = TheGameObjectFactory::getInstance()->create(e->Attribute("type"));
			gameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
			objectLayer->getGameObjects()->push_back(gameObject);
		}
	}
	layers->push_back(objectLayer);
}