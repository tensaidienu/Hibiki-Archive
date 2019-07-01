#include "Enemy.h"

using namespace std;

Enemy::Enemy() : SDLGameObject(){ }

void Enemy::load(const LoaderParams *params) {
    SDLGameObject::load(params);
    velocity.setY(2);
    velocity.setX(0.001);
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::update() {
    int numFrames = 2;
    currentFrame = int(((SDL_GetTicks() / 100) % numFrames));
    if(position.getY() < 0) {
        velocity.setY(2);
    } else if(position.getY() > 400) {
        velocity.setY(-2);
    }
    SDLGameObject::update();
}

void Enemy::clean() {
    
}
