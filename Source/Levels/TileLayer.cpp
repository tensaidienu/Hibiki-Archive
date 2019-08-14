#include "SDL2/SDL.h"

#include "TileLayer.h"

#include "../GameController.h"
#include "../GlobalVariables.h"

#include "../Managers/TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : tileSize(tileSize), tilesets(tilesets), position(0,0), velocity(0,0) {
    this->numColumns = (TheGame::getInstance()->getGameWidth()+10 / this->tileSize);
    this->numRows = (TheGame::getInstance()->getGameHeight() / this->tileSize);
}

TileLayer::~TileLayer() {
    for (auto it : this->tileIDs) {
        it.clear();
    }
    this->tileIDs.clear();
}

void TileLayer::update() {
    //position += velocity;
    //velocity.setX(1);
}

void TileLayer::render() {
    int x = 0, y = 0, x2 = 0, y2 = 0, id = 0;
    bool flippedHorizontally = false, flippedVertically = false, flippedDiagonally = false;

    x = this->position.getX() / this->tileSize;
    y = this->position.getY() / this->tileSize;
    x2 = int(this->position.getX()) % this->tileSize;
    y2 = int(this->position.getY()) % this->tileSize;
    for(int i = 0; i < this->numRows; i++) {
        for(int j = 0; j < this->numColumns; j++) {
            if (!tileIDs.empty()) { 
                id = this->tileIDs[i][j + x];
            }
            if(id == 0) {
                continue;
            }

            // Read out the flags
            flippedHorizontally = (id & (int)FLIPPED_HORIZONTALLY_FLAG);
            flippedVertically = (id & (int)FLIPPED_VERTICALLY_FLAG);
            flippedDiagonally = (id & (int)FLIPPED_DIAGONALLY_FLAG);
            //bool flippedHorizontally = (id & (int)FLIPPED_HORIZONTALLY_FLAG);
            //bool flippedVertically = (id & (int)FLIPPED_VERTICALLY_FLAG);
            //bool flippedDiagonally = (id & (int)FLIPPED_DIAGONALLY_FLAG);

            // Clear the flags
            id &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            Tileset tileset = getTilesetByID(id);
            id--;

            if(tileset.numColumns > 0){
                if (flippedHorizontally) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * this->tileSize) - x2) + this->offsetX, ((i * this->tileSize) - y2) + this->offsetY, this->tileSize, this->tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_HORIZONTAL);
                } else if (flippedVertically) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * this->tileSize) - x2) + this->offsetX, ((i * this->tileSize) - y2) + this->offsetY, this->tileSize, this->tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_VERTICAL);
                } else if (flippedDiagonally) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * this->tileSize) - x2) + this->offsetX, ((i * this->tileSize) - y2) + this->offsetY, this->tileSize, this->tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
                } else {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * this->tileSize) - x2) + this->offsetX, ((i * this->tileSize) - y2) + this->offsetY, this->tileSize, this->tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_NONE);
                }
            } else {
                //SDL_Log("TILESET ERROR!!!");
            }
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) {
	for (int i = 0; i < this->tilesets.size(); i++) {
		if (i + 1 <= this->tilesets.size() - 1) {
			if (tileID >= this->tilesets[i].firstGridID && tileID < this->tilesets[i + 1].firstGridID) {
				return this->tilesets[i];
			}
		}
		else {
			return this->tilesets[i];
		}
	}
	Tileset t;
	return t;
}