#ifndef __TileLayer_h__
#define __TileLayer_h__

#include "Layer.h"
#include "Level.h"
#include "../Vector2D.h"

class TileLayer : public Layer {
    public:
        TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
        virtual void update();
        virtual void render();
        void setTileIDs(const std::vector<std::vector<int>>& data){ tileIDs = data; }
        void setTileSize(int tileSize) { this->tileSize = tileSize; }
        Tileset getTilesetByID(int tileID);
        int offsetX;
        int offsetY;
    private:
        int numColumns;
        int numRows;
        int tileSize;        
        Vector2D position;
        Vector2D velocity;
        const std::vector<Tileset> &tilesets;
        std::vector<std::vector<int>> tileIDs;
        // Bits on the far end of the 32-bit global tile ID are used for tile flags
        const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
        const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
};

#endif