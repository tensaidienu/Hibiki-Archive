#include "SDL2/SDL.h"

#include "Level.h"
#include "../Managers/InputManager.h"

Level::Level(){
    functionCallbacks.emplace("COLLISION_TEST", COLLISION_TEST);
    functionCallbacks.emplace("CLICK_TEST", CLICK_TEST);
    this->released = true;
}

Level::~Level() {
    this->tilesets.clear();
    
    for (auto it : this->layers) {
        delete it;
    }
    this->layers.clear();

    for (auto it : this->players) {
        delete it;
    }
    this->players.clear();

    for (auto it : this->enemies) {
        delete it;
    }
    this->enemies.clear();

    for (auto it : this->staticsGameObjects) {
        delete it;
    }
    this->staticsGameObjects.clear();
}

void Level::update() {
    layersUpdate();
    playersUpdate();
    enemiesUpdate();
    staticsGameObjectsUpdate();
}

void Level::render() {
    for(int i = 0; i < this->layers.size(); i++) {
        this->layers[i]->render();
    }
    for(int i = 0; i < this->players.size(); i++) {
        this->players[i]->draw();
    }
    for(int i = 0; i < this->enemies.size(); i++) {
        this->enemies[i]->draw();
    }
    for(int i = 0; i < this->staticsGameObjects.size(); i++) {
        this->staticsGameObjects[i]->draw();
    }
}

void Level::clear() {
    this->tilesets.clear();
    this->layers.clear();
}

void Level::layersUpdate() {
    for(int l = 0; l < this->layers.size(); l++) {
        this->layers[l]->update();
    }
}

void Level::playersUpdate() {
    float velocity = 5.5;

    for(int p = 0; p < this->players.size(); p++) {
        //BASIC GRAVITY WITHOUT ACCELERTATION USING BASIC VELOCITY
        for(int s = 0; s < this->staticsGameObjects.size(); s++) {
            if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER|| 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                dynamic_cast<CollisionGameObject*>(this->players[p])->getVelocity().setY(velocity);
                checkBlockCollisionDown(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
            }
        }
        for(int e = 0; e < this->enemies.size(); e++) {
            checkBlockCollisionDown(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->enemies[e]));
        }

        if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            dynamic_cast<CollisionGameObject*>(this->players[p])->getVelocity().setX(velocity);
            dynamic_cast<DynamicGameObject*>(this->players[p])->setDirection(1);
            for(int s = 0; s < this->staticsGameObjects.size(); s++) {
                if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionRight(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
                }
            }
            for(int e = 0; e < this->enemies.size(); e++) {
                if(dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionRight(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->enemies[e]));
                }
            }
        }
        if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            dynamic_cast<CollisionGameObject*>(this->players[p])->getVelocity().setX(velocity*-1);
            dynamic_cast<DynamicGameObject*>(this->players[p])->setDirection(2);
            for(int s = 0; s < this->staticsGameObjects.size(); s++) {
                if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER|| 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionLeft(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
                }
            }
            for(int e = 0; e < this->enemies.size(); e++) {
                if(dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionLeft(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->enemies[e]));
                }
            }
        }
        if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_UP)) {
            dynamic_cast<CollisionGameObject*>(this->players[p])->getVelocity().setY(velocity*-1);
            //dynamic_cast<DynamicGameObject*>(players[i])->setDirection(3);
            for(int s = 0; s < this->staticsGameObjects.size(); s++) {
                if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER|| 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionTop(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
                }
            }
            for(int e = 0; e < this->enemies.size(); e++) {
                if(dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionTop(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->enemies[e]));
                }
            }
        }
        if(TheInputManager::getInstance()->isKeyDown(SDL_SCANCODE_DOWN)) {
            dynamic_cast<CollisionGameObject*>(this->players[p])->getVelocity().setY(velocity);
            //dynamic_cast<DynamicGameObject*>(players[i])->setDirection(4);
            for(int s = 0; s < this->staticsGameObjects.size(); s++) {
                if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER|| 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionDown(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
                }
            }
            for(int e = 0; e < this->enemies.size(); e++) {
                if(dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER || 
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                    checkBlockCollisionDown(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->enemies[e]));
                }
            }
        }
        this->players[p]->update();
    }
}

void Level::enemiesUpdate() {
    float velocity = 2.5;

    for(int e = 0; e < this->enemies.size(); e++) {
        //BASIC GRAVITY WITHOUT ACCELERTATION USING BASIC VELOCITY
        for(int s = 0; s < this->staticsGameObjects.size(); s++) {
            if(dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK || 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_AND_TRIGGER|| 
                dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType() == COLLISION_BLOCK_CLICK_TRIGGER) {
                dynamic_cast<CollisionGameObject*>(this->enemies[e])->getVelocity().setY(velocity);
                checkBlockCollisionDown(dynamic_cast<CollisionGameObject*>(this->enemies[e]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]));
            }
        }

        this->enemies[e]->update();
    }
}

void Level::staticsGameObjectsUpdate() {
    //Check player collisions
    for(int p = 0; p < this->players.size(); p++) {
        //PLAYER COLLIDE WITH ENEMY
        /*for(int e = 0; e < enemies.size(); e++) {
            enemies[e]->draw();
        }*/
        //PLAYER COLLIDE WITH STATIC GAMEOBJECT
        for(int s = 0; s < this->staticsGameObjects.size(); s++) {
            switch (dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s])->getCollider().getType()) {
                case COLLISION_TRIGGER:
                    if(checkCollision(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]))){
                        functionCallbacks[dynamic_cast<StaticGameObject*>(this->staticsGameObjects[s])->getID()]();
                    }
                    break;
                case COLLISION_BLOCK_AND_TRIGGER:
                    if(checkCollision(dynamic_cast<CollisionGameObject*>(this->players[p]), dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]))){
                        functionCallbacks[dynamic_cast<StaticGameObject*>(this->staticsGameObjects[s])->getID()]();
                    }
                    //SDL_Log("-----COLLISION_BLOCK_AND_TRIGGER DETECTED-----");
                    break;
                case CLICK_TRIGGER:
                    mousePos = TheInputManager::getInstance()->getMousePosition();
                    if(checkMouseClick( dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]))) {
                        if(TheInputManager::getInstance()->getMouseButtonState(LEFT) && released) {
                            functionCallbacks[dynamic_cast<StaticGameObject*>(this->staticsGameObjects[s])->getID()]();
                            released = false;
                        }
                    } else {
                        released = true;
                    }
                    break;
                case COLLISION_BLOCK_CLICK_TRIGGER:
                    mousePos = TheInputManager::getInstance()->getMousePosition();
                    if(checkMouseClick( dynamic_cast<CollisionGameObject*>(this->staticsGameObjects[s]))) {
                        if(TheInputManager::getInstance()->getMouseButtonState(LEFT) && released) {
                            functionCallbacks[dynamic_cast<StaticGameObject*>(this->staticsGameObjects[s])->getID()]();
                            released = false;
                        }
                    } else {
                        released = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

bool Level::checkCollision(CollisionGameObject* collider1, CollisionGameObject* collider2) {
    //Basic check with the problem of velocity, the greater the velocity the far the object stops.
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = collider1->getPosition().getX() + collider1->getCollider().getOffset().getX();
    rightA = collider1->getPosition().getX() + collider1->getWidth();
    topA = collider1->getPosition().getY() + collider1->getCollider().getOffset().getY();
    bottomA = collider1->getPosition().getY() + collider1->getHeight();

    //Calculate the sides of rect B
    leftB = collider2->getPosition().getX() + collider2->getCollider().getOffset().getX();
    rightB = collider2->getPosition().getX() + collider2->getWidth();
    topB = collider2->getPosition().getY() + collider2->getCollider().getOffset().getY();
    bottomB = collider2->getPosition().getY() + collider2->getHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false;}
    if( rightA <= leftB ){return false;}
    if( leftA >= rightB ){return false;}

    return true;
}

bool Level::checkBlockCollisionRight(CollisionGameObject* collider1, CollisionGameObject* collider2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    float velocity;

    velocity = collider1->getVelocity().getX();
    
    //Calculate the sides of rect B
    leftA = collider1->getPosition().getX() + collider1->getCollider().getOffset().getX();
    rightA = collider1->getPosition().getX() + collider1->getWidth() + velocity;
    topA = collider1->getPosition().getY() + collider1->getCollider().getOffset().getY();
    bottomA = collider1->getPosition().getY() + collider1->getHeight();
    
    //Calculate the sides of rect B
    leftB = collider2->getPosition().getX() + collider2->getCollider().getOffset().getX();
    rightB = collider2->getPosition().getX() + collider2->getWidth();
    topB = collider2->getPosition().getY() + collider2->getCollider().getOffset().getY();
    bottomB = collider2->getPosition().getY() + collider2->getHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false;}
    if( rightA <= leftB ){return false;}
    if( leftA >= rightB ){return false;}

    dynamic_cast<DynamicGameObject*>(collider1)->getVelocity().setX((leftB - (rightA-velocity)));

    return false;
}

bool Level::checkBlockCollisionLeft(CollisionGameObject* collider1, CollisionGameObject* collider2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    float velocity;

    velocity = collider1->getVelocity().getX();
    
    //Calculate the sides of rect B
    leftA = collider1->getPosition().getX() + collider1->getCollider().getOffset().getX() + velocity;
    rightA = collider1->getPosition().getX() + collider1->getWidth();
    topA = collider1->getPosition().getY() + collider1->getCollider().getOffset().getY();
    bottomA = collider1->getPosition().getY() + collider1->getHeight();
    
    //Calculate the sides of rect B
    leftB = collider2->getPosition().getX() + collider2->getCollider().getOffset().getX();
    rightB = collider2->getPosition().getX() + collider2->getWidth();
    topB = collider2->getPosition().getY() + collider2->getCollider().getOffset().getY();
    bottomB = collider2->getPosition().getY() + collider2->getHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false;}
    if( rightA <= leftB ){return false;}
    if( leftA >= rightB ){return false;}

    dynamic_cast<DynamicGameObject*>(collider1)->getVelocity().setX(((leftA-velocity) - rightB)*-1);

    return false;
}

bool Level::checkBlockCollisionTop(CollisionGameObject* collider1, CollisionGameObject* collider2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    float velocity = 0.5;

    velocity = collider1->getVelocity().getY();
    
    //Calculate the sides of rect B
    leftA = collider1->getPosition().getX() + collider1->getCollider().getOffset().getX();
    rightA = collider1->getPosition().getX() + collider1->getWidth();
    topA = collider1->getPosition().getY() + collider1->getCollider().getOffset().getY() + velocity;
    bottomA = collider1->getPosition().getY() + collider1->getHeight();
    
    //Calculate the sides of rect B
    leftB = collider2->getPosition().getX() + collider2->getCollider().getOffset().getX();
    rightB = collider2->getPosition().getX() + collider2->getWidth();
    topB = collider2->getPosition().getY() + collider2->getCollider().getOffset().getY();
    bottomB = collider2->getPosition().getY() + collider2->getHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false;}
    if( rightA <= leftB ){return false;}
    if( leftA >= rightB ){return false;}

    dynamic_cast<DynamicGameObject*>(collider1)->getVelocity().setY(((topA-velocity) - bottomB)*-1);

    return false;
}

bool Level::checkBlockCollisionDown(CollisionGameObject* collider1, CollisionGameObject* collider2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    float velocity = 0.5;

    velocity = collider1->getVelocity().getY();
    
    //Calculate the sides of rect B
    leftA = collider1->getPosition().getX() + collider1->getCollider().getOffset().getX();
    rightA = collider1->getPosition().getX() + collider1->getWidth();
    topA = collider1->getPosition().getY() + collider1->getCollider().getOffset().getY();
    bottomA = collider1->getPosition().getY() + collider1->getHeight() + velocity;
    
    //Calculate the sides of rect B
    leftB = collider2->getPosition().getX() + collider2->getCollider().getOffset().getX();
    rightB = collider2->getPosition().getX() + collider2->getWidth();
    topB = collider2->getPosition().getY() + collider2->getCollider().getOffset().getY();
    bottomB = collider2->getPosition().getY() + collider2->getHeight();    

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){return false;}
    if( topA >= bottomB ){return false;}
    if( rightA <= leftB ){return false;}
    if( leftA >= rightB ){return false;}

    dynamic_cast<DynamicGameObject*>(collider1)->getVelocity().setY(topB - (bottomA-velocity));

    return false;
}

bool Level::checkMouseClick(CollisionGameObject* gameObject){
    return this->mousePos->getX() < gameObject->getPosition().getX() + gameObject->getWidth()
    && this->mousePos->getX() > gameObject->getPosition().getX()
    && this->mousePos->getY() < gameObject->getPosition().getY() + gameObject->getHeight()
    && this->mousePos->getY() > gameObject->getPosition().getY();
}

void Level::COLLISION_TEST() {
    SDL_Log("_____COLLISION TRIGGER DETECTED_____");
}

void Level::CLICK_TEST() {
    SDL_Log("_____CLICK ON GAMEOBJECT DETECTED_____");
}