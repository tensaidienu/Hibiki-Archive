#include "TileLayer.h"
#include "../GameController.h"
#include "../Managers/TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : tileSize(tileSize), tilesets(tilesets), position(0,0), velocity(0,0) {
    numColumns = (TheGame::getInstance()->getGameWidth()+10 / tileSize);
    numRows = (TheGame::getInstance()->getGameHeight() / tileSize);
}

void TileLayer::update() {
    //position += velocity;
    //velocity.setX(1);
}

void TileLayer::render() {
    int x, y, x2, y2 = 0;
    x = position.getX() / tileSize;
    y = position.getY() / tileSize;
    x2 = int(position.getX()) % tileSize;
    y2 = int(position.getY()) % tileSize;
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++) {
            int id = tileIDs[i][j + x];            
            if(id == 0) {
                continue;
            }
            // Read out the flags
            bool flippedHorizontally = (id & (int)FLIPPED_HORIZONTALLY_FLAG);
            bool flippedVertically = (id & (int)FLIPPED_VERTICALLY_FLAG);
            bool flippedDiagonally = (id & (int)FLIPPED_DIAGONALLY_FLAG);

            // Clear the flags
            id &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            Tileset tileset = getTilesetByID(id);
            id--;

            if(tileset.numColumns > 0){
                if (flippedHorizontally) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * tileSize) - x2) + offsetX, ((i * tileSize) - y2) + offsetY, tileSize, tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_HORIZONTAL);
                } else if (flippedVertically) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * tileSize) - x2) + offsetX, ((i * tileSize) - y2) + offsetY, tileSize, tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_VERTICAL);
                } else if (flippedDiagonally) {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * tileSize) - x2) + offsetX, ((i * tileSize) - y2) + offsetY, tileSize, tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
                } else {
                    TheTextureManager::getInstance()->drawTile(tileset.name, 0, 0, ((j * tileSize) - x2) + offsetX, ((i * tileSize) - y2) + offsetY, tileSize, tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::getInstance()->getRenderer(), SDL_FLIP_NONE);
                }
            } else {
                //std::cout << "TILESET ERROR!!!!\n";
            }
        }
    }
}

TileLayer::~TileLayer() {
    for (auto it : tileIDs) {
        it.clear();
    }
    tileIDs.clear();
}

Tileset TileLayer::getTilesetByID(int tileID) {
	for (int i = 0; i < tilesets.size(); i++) {
		if (i + 1 <= tilesets.size() - 1) {
			if (tileID >= tilesets[i].firstGridID && tileID < tilesets[i + 1].firstGridID) {
				return tilesets[i];
			}
		}
		else {
			return tilesets[i];
		}
	}
	Tileset t;
	return t;
}