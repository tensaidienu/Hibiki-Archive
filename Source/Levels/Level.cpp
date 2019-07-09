#include "Level.h"

Level::Level(){

}

void Level::render() {
    for(int i = 0; i < layers.size(); i++) {
        layers[i]->render();
    }
}

void Level::update() {
    for(int i = 0; i < layers.size(); i++) {
        layers[i]->update();
    }
}

void Level::clear() {
    tilesets.clear();
    layers.clear();
}

Level::~Level() {
    tilesets.clear();
    for (auto it : layers) {
        delete it;
    }
    layers.clear();
}