#ifndef ENEMYSPAWN_H
#define ENEMYSPAWN_H
#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

class EnemySpawn : public Component
{
    public:
        EnemySpawn(GameObject &associated, TileMap *tileMap)
        : Component(associated), tileMap(tileMap)
        {
        }

        ~EnemySpawn()
        {
        }

        void update(float dt);
        void rhythmUpdate()
        {
        }
        void rhythmReset()
        {
        }
        void render(Common::Layer layer) const
        {
        }

    private:
        TileMap *tileMap;
        int current_y = 0;
};

#endif
