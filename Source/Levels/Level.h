#ifndef __Level_h__
#define __Level_h__

#include <string>
#include <vector>

#include "Layer.h"

class LevelParser;

struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level {
    private:
        std::vector<Tileset> tilesets;
        std::vector<Layer*> layers;
        friend class LevelParser;
        Level() {}
        ~Level() {}
    public:        
        void update();
        void render();
        void clear();
        std::vector<Tileset>* getTilesets() {
            return &tilesets;
        }
        std::vector<Layer*>* getLayers() {
            return &layers;
        }
};

#endif