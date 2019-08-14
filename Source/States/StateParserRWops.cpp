#include "SDL2/SDL.h"

#include "StateParser.h"

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"
#include "../Factories/GameObjectFactory.h"

bool StateParser::parseState(std::string stateFile, std::string stateID, std::vector<GameObject*> *objects, std::vector<std::string> *textureIDs) {	
	XMLDocument xmlDoc;

	/* Load graphics */
	SDL_RWops *file;
    FILE* fp = fopen(stateFile.c_str(), "rb" );
    
	char* doc_contents;
	file = SDL_RWFromFile(stateFile.c_str(), "rb");
	size_t file_length = SDL_RWseek(file, 0, SEEK_END);
	(doc_contents) = new char[file_length + 1]; // allow an extra character for '\0'
	SDL_RWseek(file, 0, SEEK_SET);
	int n_blocks = SDL_RWread(file, (doc_contents), 1, file_length);
	SDL_RWclose(file);
	(doc_contents)[file_length] = '\0';

    if (xmlDoc.Parse(doc_contents) != 0) {
		SDL_LogError(0, "%s: Error while loading the file  ----->>> %s", xmlDoc.Error(), stateFile.c_str());
        //std::cerr << xmlDoc.Error() << " Error while loading the file  ----->>>  " << stateFile.c_str() << ERROR_FILE << std::endl;
		return false; // erro a carregar o ficheiro
	}
	
	XMLElement* root = xmlDoc.RootElement();
	XMLElement* stateRoot = 0;
	
	//get state ROOT
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == stateID) {
			stateRoot = e;
			break;
		}
	}
	
	//get Textures root
	XMLElement* pTextureRoot = 0;
	for (XMLElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) {
			pTextureRoot = e;
			break;
		}
	}
	
	parseTextures(pTextureRoot, textureIDs);

	//get objects root
	XMLElement* pObjectRoot = 0;
	for (XMLElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
			break;
		}
	}
	parseObjects(pObjectRoot, objects);	
	return true;
}

void StateParser::parseTextures(XMLElement* stateRoot, std::vector<std::string> *textureIDs) {
	for (XMLElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		textureIDs->push_back(idAttribute);
		TheTextureManager::getInstance()->loadImg(filenameAttribute, idAttribute, TheGame::getInstance()->getRenderer());
	}
}

void StateParser::parseObjects(XMLElement* stateRoot, std::vector<GameObject*> *objects) {
	for (XMLElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
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