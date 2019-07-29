#include "StaticGameObject.h"
#include "../GameController.h"
#include "../Managers/TextureManager.h"

StaticGameObject::StaticGameObject() : CollisionGameObject(){ }

void StaticGameObject::load(const LoaderParams* params) {
    position = Vector2D(params->getX(), params->getY());
    width = params->getWidth();
    height = params->getHeight();
    gameObjectID = params->getTextureID();
    currentRow = 1;
    currentFrame = 0;
    numFrames = params->getNumFrames();
    collider.load(params->getX(), params->getY(), params->getType());
}

void StaticGameObject::draw() {
    collider.draw(width, height);
    /*SDL_Rect rect;
    rect.x = collider.getSize().getX();
    rect.y = collider.getSize().getY();
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 0, 255, 255);
    TheTextureManager::getInstance()->drawRect(TheGame::getInstance()->getRenderer(), rect);*/
}

void StaticGameObject::update() {
    //velocity += acceleration;
    //position += velocity;
}

void StaticGameObject::clean() {
    
}