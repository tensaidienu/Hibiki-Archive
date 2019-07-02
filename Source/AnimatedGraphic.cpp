#include "SDL2/SDL.h"

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject(){ }

void AnimatedGraphic::load(const LoaderParams *params) {
    SDLGameObject::load(params);
	animSpeed = params->getAnimSpeed();
}

void AnimatedGraphic::draw() {
	SDLGameObject::draw();
}

void AnimatedGraphic::update() {
	currentRow = int(((SDL_GetTicks() / (1000 / animSpeed)) % 2)+1);
}

void AnimatedGraphic::clean() {

}