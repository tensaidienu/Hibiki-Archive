#include "SDL2/SDL.h"

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : DynamicGameObject(){}

void AnimatedGraphic::load(const LoaderParams *params) {
    DynamicGameObject::load(params);
	animSpeed = params->getAnimSpeed();
}

void AnimatedGraphic::draw() {
	DynamicGameObject::draw();
}

void AnimatedGraphic::update() {
	currentRow = int(((SDL_GetTicks() / (1000 / animSpeed)) % 2)+1);
}

void AnimatedGraphic::clear() {

}