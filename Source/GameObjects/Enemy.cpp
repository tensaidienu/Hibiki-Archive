#include "Enemy.h"

using namespace std;

Enemy::Enemy() : DynamicGameObject(){ }

void Enemy::load(const LoaderParams *params) {
    DynamicGameObject::load(params);
    velocity.setY(2);
    velocity.setX(0.001);
}

void Enemy::draw() {
    DynamicGameObject::draw();
}

void Enemy::update() {
    currentFrame = int(((SDL_GetTicks() / 250) % numFrames));    
    velocity += acceleration;
    position += velocity;
    collider.getSize().setX(position.getX());
    collider.getSize().setY(position.getY());
    velocity.setX(0);
    velocity.setY(0);
    if(position.getX() < 5) {
        velocity.setX(2);
    } else if(position.getX() > 700) {
        velocity.setX(-2);
    }
}

void Enemy::clean() {
    
}
