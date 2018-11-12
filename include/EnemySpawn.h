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
        : Component(associated), tile_map(tile_map) {}

        ~EnemySpawn() {}

    void update(float delta_time);
    void rhythmUpdate() {}
    void rhythmReset() {}
    void render(Common::layer layer) const {}

    private:
        TileMap *tile_map;
        int current_y = 0;
};

#endif
