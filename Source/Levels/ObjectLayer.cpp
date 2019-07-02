#include "ObjectLayer.h"

void ObjectLayer::update() {
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->update();
    }
}

void ObjectLayer::render() {
    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->draw();
    }
}