#ifndef ENEMYDEATH_H
#define ENEMYDEATH_H
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

class EnemyDeath : public Component
{
    public:
        EnemyDeath(GameObject &associated) : Component(associated) {}

        ~EnemyDeath() {}

    void update(float delta_time);
    void rhythmUpdate() {}
    void RhythmReset() {}
    void render(Common::layer layer) const {}

    private:
        // Cada enemy tera sua própria morte, diferente do EnemySpawn que é um geral
        std::weak_ptr <GameObject> enemy;
};

#endif
