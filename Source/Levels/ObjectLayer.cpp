#include "ObjectLayer.h"

ObjectLayer::ObjectLayer() {

}

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

ObjectLayer::~ObjectLayer() {
    for (auto it : gameObjects) {
        delete it;
    }
    gameObjects.clear();
}

