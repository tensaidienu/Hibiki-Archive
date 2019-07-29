#include "Collider.h"
#include "../GameController.h"
#include "../Managers/TextureManager.h"

using namespace std;

Collider::Collider() { }

void Collider::load(float x, float y, std::string type) {
    this->size = Vector2D(x, y);
    this->gravity = Vector2D(0, 0);
    this->offset = Vector2D(0, 0);
    this->type = TheGlobalVariables::getInstance()->getCollisionTypeByString(type);
}

/*
void Collider::load(const LoaderParams* params) {
    size = Vector2D(params->getX(), params->getY());
    //gravity = Vector2D(0, 0);
    //offset = params->getWidth();
}
*/

void Collider::draw(int width, int height) {
    SDL_Rect rect;
    rect.x = size.getX() + offset.getX();
    rect.y = size.getY() + offset.getY();
    rect.w = width;
    rect.h = height;

    switch (type) {
        case COLLISION_BLOCK:
            SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 255, 0, 0, 255);
            break;
        case COLLISION_TRIGGER:
            SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 255, 0, 255);
            break;
        case COLLISION_BLOCK_AND_TRIGGER:
            SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 255, 255, 0, 255);
            break;
        case CLICK_TRIGGER:
            SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 0, 0, 255, 255);
            break;
        case COLLISION_BLOCK_CLICK_TRIGGER:
            SDL_SetRenderDrawColor(TheGame::getInstance()->getRenderer(), 255, 0, 255, 255);
            break;
    }
    TheTextureManager::getInstance()->drawRect(TheGame::getInstance()->getRenderer(), rect);
}

void Collider::update() {
    //position += velocity;
}

void Collider::clean() {
    
}

Collider::~Collider() {
    
}