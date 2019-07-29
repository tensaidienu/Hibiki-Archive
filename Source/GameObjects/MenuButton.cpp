#include "MenuButton.h"
#include "../Managers/InputManager.h"

MenuButton::MenuButton() : DynamicGameObject(){ }

void MenuButton::load(const LoaderParams* params) {
	DynamicGameObject::load(params);
	this->callbackID = params->getCallbackID();
	currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
    DynamicGameObject::draw(); // use the base class drawing
}

void MenuButton::update() {    
    Vector2D* mousePos = TheInputManager::getInstance()->getMousePosition();
    if(mousePos->getX() < (position.getX() + width)
    && mousePos->getX() > position.getX()
    && mousePos->getY() < (position.getY() + height)
    && mousePos->getY() > position.getY()) {
        currentFrame = MOUSE_OVER;
        if(TheInputManager::getInstance()->getMouseButtonState(LEFT) && released) {
            currentFrame = CLICKED;
            functionCallback();
            //callback(); // call our callback function
            released = false;
        }
    } else {
        released = true;
        currentFrame = MOUSE_OUT;
    }
}

void MenuButton::setFuncCallback(std::function<void()> func){
    functionCallback = func;
}

void MenuButton::clean() {
    DynamicGameObject::clean();
}

MenuButton::~MenuButton() {
    
}