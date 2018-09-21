//Header file for the class EnemyDeath, contains the headers for all the
//methods of the class.

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

        void update(float dt);
        void rhythmUpdate() {}
        void rhythmReset() {}
        void render(Common::Layer layer) const {}

    private:
        std::weak_ptr <GameObject> enemy;//Each enemy will have their own death
};

#endif
