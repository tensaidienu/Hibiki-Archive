#include "CollisionGameObject.h"
#include "../GameController.h"
#include "../Managers/TextureManager.h"

CollisionGameObject::CollisionGameObject() : GameObject(){ }

void CollisionGameObject::load(const LoaderParams* params) {
    /*position = Vector2D(params->getX(), params->getY());
    velocity = Vector2D(0, 0);
    acceleration = Vector2D(0, 0);
    width = params->getWidth();
    height = params->getHeight();
    collider.load(params->getX(), params->getY());*/
}

void CollisionGameObject::draw() {
    /*switch (direction) {
    case 1:
        TheTextureManager::getInstance()->drawFrame(this->textureID, (int) position.getX(), (int) position.getY(), this->width, this->height, this->currentRow, this->currentFrame, TheGame::getInstance()->getRenderer());
        break;
    case 2:
        TheTextureManager::getInstance()->drawFrame(this->textureID, (int) position.getX(), (int) position.getY(), this->width, this->height, this->currentRow, this->currentFrame, TheGame::getInstance()->getRenderer(), SDL_FLIP_HORIZONTAL);
        break;
    
    default:
        TheTextureManager::getInstance()->drawFrame(this->textureID, (int) position.getX(), (int) position.getY(), this->width, this->height, this->currentRow, this->currentFrame, TheGame::getInstance()->getRenderer());
        break;
    }

    SDL_Rect rect;
    rect.x = collider.getSize().getX();
    rect.y = collider.getSize().getY();
    rect.w = width;
    rect.h = height;*/

    //SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 0, 255, 255);
    //TheTextureManager::getInstance()->drawRect(TheGame::getInstance()->getRenderer(), rect);
    ///TextureManager::getInstance()->drawFrame(this->textureID, (int) position.getX(), (int) position.getY(), this->width, this->height, this->currentRow, this->currentFrame, TheGame::getInstance()->getRenderer());
    /*if(velocity.getX() > 0) {
        TextureManager::getInstance()->drawFrame(textureID,
        (Uint32)position.getX(), (Uint32)position.getY(),
        width, height, currentRow, currentFrame,
        TheGame::getInstance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::getInstance()->drawFrame(textureID,
        (Uint32)position.getX(), (Uint32)position.getY(),
        width, height, currentRow, currentFrame,
        TheGame::getInstance()->getRenderer());
    }*/
}

void CollisionGameObject::update() {
    /*velocity += acceleration;
    position += velocity;
    collider.load(position.getX(), position.getY());*/
}

void CollisionGameObject::clean() {
    
}