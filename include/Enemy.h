#ifndef ENEMY_H
#define ENEMY_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "Alan.h"
#include "Component.h"
#include "InputManager.h"
#include "Interpol.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

class Enemy : public Component {
  public:
    enum direction { left = 0, right };
    enum state { NONE_S = 0, IDLE_S, WALKIN_S, DIE_S, STATE_MAX };

    Enemy(GameObject& associated, int enemy_type = 1);

    ~Enemy() {}

    void update(float delta_time);
    void rhythmUpdate()
    {
        num_beats++;

        if (!movement_allowed && num_beats > 1) 
        {
            movement_allowed = true;
            num_beats = 0;
        }
    }
    void rhythmReset() {}
    void render(Common::layer layer) const {}

    Vec2 getGridPosition()
    {
        return associated.getGridPosition();
    }

    void movementDenied()
    {
        movement_allowed = false;
    }

    direction GetMovementDirection()
    {
        return movement_direction;
    }
    state getState()
    {
        return state;
    }

    void setAsHit()
    {
        associated.getComponent<Interpol*>()->is_hit = true;
        movement_allowed = false;
    }

    bool verifyDeath(Alan* alan);

    void takeDamage(int damage)
    {
        life_enemy -= damage;
    }

    void ShouldTakeDamage(Alan* alan);

    void IsSurrounded();

    bool movement_allowed = false;

  private:
    direction movement_direction = direction::left;

    // 2<=range<=7
    int range, steps = 0;
    state state = state::IDLE_S;

    int num_beats = 0;

    int life_enemy;

    Vec2 tileMapPos;

    Sprite::SpriteState EState[state::STATE_MAX];
    InputManager& input;

    bool damage_taken = false;
};

#endif  // ENEMY_H