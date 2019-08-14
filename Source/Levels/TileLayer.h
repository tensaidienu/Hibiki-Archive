#ifndef __TileLayer_h__
#define __TileLayer_h__

#include "Layer.h"
#include "Level.h"
#include "../Vector2D.h"

class TileLayer : public Layer {
    private:
        int numColumns = 0;
        int numRows = 0;
        int tileSize = 0;
        Vector2D position = Vector2D();
        Vector2D velocity = Vector2D();
        const std::vector<Tileset> &tilesets;
        std::vector<std::vector<int> > tileIDs = std::vector<std::vector<int> >();
        // Bits on the far end of the 32-bit global tile ID are used for tile flags
        const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
        const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
    public:
        TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
        ~TileLayer();
        virtual void update();
        virtual void render();
        void setTileIDs(const std::vector<std::vector<int> >& data){ this->tileIDs = data; }
        void setTileSize(int tileSize) { this->tileSize = tileSize; }
        Tileset getTilesetByID(int tileID);
        int offsetX = 0;
        int offsetY = 0;
};

#endif