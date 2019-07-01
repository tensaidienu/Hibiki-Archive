#include "Player.h"
#include "InputHandler.h"

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
    Vector2D* target = TheInputHandler::getInstance()->getMousePosition();
    velocity = *target - position;
    velocity /= 50;

    //--------------------------------------------PLAYER KEYBOARD EVENTS--------------------------------------------
    /*if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        velocity.setX(2);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        velocity.setX(-2);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_UP)) {
        velocity.setY(-2);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        velocity.setY(2);
    }*/

    //--------------------------------------------PLAYER MOUSE EVENTS--------------------------------------------
    //Move player using mouse position
    //Vector2D* vec = TheInputHandler::getInstance()->getMousePosition();
    //velocity = (*vec - position) / 150;
    
    //if(TheInputHandler::getInstance()->getMouseButtonState(LEFT)) {
        //velocity.setX(1);
    //}

    //--------------------------------------------PLAYER JOYSTICK EVENTS--------------------------------------------
    /*if(TheInputHandler::getInstance()->isJoysticksInitialised()) {
        if(TheInputHandler::getInstance()->xvalue(0, 1) > 0 || TheInputHandler::getInstance()->xvalue(0, 1) < 0) {
            velocity.setX(1 * TheInputHandler::getInstance()->xvalue(0, 1));
        }
        if(TheInputHandler::getInstance()->yvalue(0, 1) > 0 || TheInputHandler::getInstance()->yvalue(0, 1) < 0) {
            velocity.setY(1 * TheInputHandler::getInstance()->yvalue(0, 1));
        }
        if(TheInputHandler::getInstance()->xvalue(0, 2) > 0 || TheInputHandler::getInstance()->xvalue(0, 2) < 0) {
            velocity.setX(1 * TheInputHandler::getInstance()->xvalue(0, 2));
        }
        if(TheInputHandler::getInstance()->yvalue(0, 2) > 0 || TheInputHandler::getInstance()->yvalue(0, 2) < 0) {
            velocity.setY(1 * TheInputHandler::getInstance()->yvalue(0, 2));
        }
    }*/
}