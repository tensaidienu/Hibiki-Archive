#ifndef __Level_h__
#define __Level_h__

#include <functional>
#include <string>
#include <vector>

#include "Layer.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/CollisionGameObject.h"
#include "../GameObjects/StaticGameObject.h"
#include "../GameObjects/Collider.h"

class LevelParser;

struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level {
    private:
        bool checkCollision(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkBlockCollision(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkBlockCollisionRight(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkBlockCollisionLeft(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkBlockCollisionTop(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkBlockCollisionDown(CollisionGameObject* collider1, CollisionGameObject* collider2);
        bool checkMouseClick(CollisionGameObject* gameObject);

        void layersUpdate();
        void playersUpdate();
        void enemiesUpdate();
        void staticsGameObjectsUpdate();

        void static COLLISION_TEST();
        void static CLICK_TEST();

        std::vector<GameObject*> players;
        std::vector<GameObject*> enemies;
        std::vector<GameObject*> staticsGameObjects;
        std::map<std::string, std::function<void()>> functionCallbacks;

        std::vector<Tileset> tilesets;
        std::vector<Layer*> layers;
        friend class LevelParser;

        enum button_state {
		    MOUSE_OUT = 0,
		    MOUSE_OVER = 1,
		    CLICKED = 2
	    };
        bool released;
        Vector2D* mousePos;
    public:
        Level();
        ~Level();
        void update();
        void render();
        void clear();
        
        std::vector<GameObject*>* getPlayers() {
            return &players;
        }
        std::vector<GameObject*>* getEnemies() {
            return &enemies;
        }
        std::vector<GameObject*>* getStaticsGameObjects() {
            return &staticsGameObjects;
        }
        
        std::vector<Tileset>* getTilesets() {
            return &tilesets;
        }
        std::vector<Layer*>* getLayers() {
            return &layers;
        }        
};

#endif