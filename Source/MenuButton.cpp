#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : SDLGameObject(){ }

void MenuButton::load(const LoaderParams* params) {
	SDLGameObject::load(params);
	this->callbackID = params->getCallbackID();
	currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
    SDLGameObject::draw(); // use the base class drawing
}

void MenuButton::update() {    
    Vector2D* mousePos = TheInputHandler::getInstance()->getMousePosition();
    if(mousePos->getX() < (position.getX() + width)
    && mousePos->getX() > position.getX()
    && mousePos->getY() < (position.getY() + height)
    && mousePos->getY() > position.getY()) {
        currentFrame = MOUSE_OVER;
        if(TheInputHandler::getInstance()->getMouseButtonState(LEFT) && released) {
            currentFrame = CLICKED;
            callback(); // call our callback function
            released = false;
        }
    } else {
        released = true;
        currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}