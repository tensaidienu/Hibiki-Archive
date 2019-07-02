#include "StateParser.h"
#include "../Managers/TextureManager.h"
#include "../GameController.h"
#include "../Factories/GameObjectFactory.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject*> *objects, std::vector<std::string> *textureIDs) {	
	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile(stateFile)) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false; // erro a carregar o ficheiro
	}

	TiXmlElement* root = xmlDoc.RootElement();
	TiXmlElement* stateRoot = 0;
	//get state ROOT
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == stateID) {
			stateRoot = e;
			break;
		}
	}
	//get Textures root
	TiXmlElement* pTextureRoot = 0;
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) {
			pTextureRoot = e;
			break;
		}
	}
	parseTextures(pTextureRoot, textureIDs);

	//get objects root
	TiXmlElement* pObjectRoot = 0;
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
			break;
		}
	}
	parseObjects(pObjectRoot, objects);
	return true;
}

void StateParser::parseTextures(TiXmlElement* stateRoot, std::vector<std::string> *textureIDs) {
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		textureIDs->push_back(idAttribute);
		TheTextureManager::getInstance()->loadImg(filenameAttribute, idAttribute, TheGame::getInstance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement* stateRoot, std::vector<GameObject*> *objects) {
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");

		GameObject* gameObject = TheGameObjectFactory::getInstance()->create(e->Attribute("type"));
		gameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		objects->push_back(gameObject);
	}
}