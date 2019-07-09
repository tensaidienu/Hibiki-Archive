#include "Player.h"
#include "../Managers/InputManager.h"

using namespace std;

Player::Player() : SDLGameObject(){ }

void Player::load(const LoaderParams *params) {
    SDLGameObject::load(params);
}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    velocity.setX(0);
    velocity.setY(0);
    handleInput();
    currentFrame = int(((SDL_GetTicks() / 100) % 4));
    SDLGameObject::update();
}

void Player::clean() {
    
}

void Player::handleInput() {
    //--------------------------------------------PLAYER KEYBOARD EVENTS--------------------------------------------
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        velocity.setX(2);
    }
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        velocity.setX(-2);
    }
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_UP)) {
        velocity.setY(-2);
    }
    if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        velocity.setY(2);
    }

    //--------------------------------------------PLAYER MOUSE EVENTS--------------------------------------------
    //Move player using mouse position
    //Vector2D* vec = TheInputManager::getInstance()->getMousePosition();
    //velocity = (*vec - position) / 150;
    
    //if(TheInputManager::getInstance()->getMouseButtonState(LEFT)) {
        //velocity.setX(1);
    //}

    /*Vector2D* target = TheInputManager::getInstance()->getMousePosition();
    velocity = *target - position;
    velocity /= 50;*/

    //--------------------------------------------PLAYER JOYSTICK EVENTS--------------------------------------------
    /*if(TheInputManager::getInstance()->isJoysticksInitialised()) {
        if(TheInputManager::getInstance()->xvalue(0, 1) > 0 || TheInputManager::getInstance()->xvalue(0, 1) < 0) {
            velocity.setX(1 * TheInputManager::getInstance()->xvalue(0, 1));
        }
        if(TheInputManager::getInstance()->yvalue(0, 1) > 0 || TheInputManager::getInstance()->yvalue(0, 1) < 0) {
            velocity.setY(1 * TheInputManager::getInstance()->yvalue(0, 1));
        }
        if(TheInputManager::getInstance()->xvalue(0, 2) > 0 || TheInputManager::getInstance()->xvalue(0, 2) < 0) {
            velocity.setX(1 * TheInputManager::getInstance()->xvalue(0, 2));
        }
        if(TheInputManager::getInstance()->yvalue(0, 2) > 0 || TheInputManager::getInstance()->yvalue(0, 2) < 0) {
            velocity.setY(1 * TheInputManager::getInstance()->yvalue(0, 2));
        }
    }*/
}