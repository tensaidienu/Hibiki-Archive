#include "StateParser.h"
#include "../Managers/TextureManager.h"
#include "../GameController.h"
#include "../Factories/GameObjectFactory.h"

bool StateParser::parseState(std::string stateFile, std::string stateID, std::vector<GameObject*> *objects, std::vector<std::string> *textureIDs) {	
	XMLDocument xmlDoc;

	//std::cout << "KUSO : " << stateFile << std::endl;
	//std::cout << "xmlDoc.LoadFile : " << xmlDoc.LoadFile(stateFile.c_str()) << std::endl;
	//std::cout << "!xmlDoc.LoadFile : " << !xmlDoc.LoadFile(stateFile.c_str()) << std::endl;

	if (xmlDoc.LoadFile(stateFile.c_str()) != 0) {
        std::cerr << xmlDoc.Error() << "\n";
		return false; // erro a carregar o ficheiro
	}

	
	XMLElement* root = xmlDoc.RootElement();
	XMLElement* stateRoot = 0;
	
	//get state ROOT
	for (XMLElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == stateID) {
			stateRoot = e;
			break;
		}
	}
	
	//get Textures root
	XMLElement* pTextureRoot = 0;
	for (XMLElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) {
			pTextureRoot = e;
			break;
		}
	}
	
	parseTextures(pTextureRoot, textureIDs);

	//get objects root
	XMLElement* pObjectRoot = 0;
	for (XMLElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
			break;
		}
	}
	parseObjects(pObjectRoot, objects);	
	return true;
}

void StateParser::parseTextures(XMLElement* stateRoot, std::vector<std::string> *textureIDs) {
	for (XMLElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		textureIDs->push_back(idAttribute);
		TheTextureManager::getInstance()->loadImg(filenameAttribute, idAttribute, TheGame::getInstance()->getRenderer());
	}
}

void StateParser::parseObjects(XMLElement* stateRoot, std::vector<GameObject*> *objects) {
	for (XMLElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		int x, y, width, height, numFrames, animSpeed = 0;
		std::string textureID, callbackID;
		
		e->QueryIntAttribute("x", &x);
		e->QueryIntAttribute("y", &y);
		e->QueryIntAttribute("width", &width);
		e->QueryIntAttribute("height", &height);
		e->QueryIntAttribute("numFrames", &numFrames);
		//e->QueryIntAttribute("callbackID", &callbackID);
		callbackID = e->Attribute("callbackID");
		e->QueryIntAttribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");

		GameObject* gameObject = TheGameObjectFactory::getInstance()->create(e->Attribute("type"));
		gameObject->load(new LoaderParams(x, y, width, height, textureID, callbackID, numFrames, animSpeed));
		objects->push_back(gameObject);
	}
}