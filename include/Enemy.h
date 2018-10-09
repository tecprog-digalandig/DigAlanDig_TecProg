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
    enum Direction { LEFT = 0, RIGHT };
    enum State { NONE_S = 0, IDLE_S, WALKIN_S, DIE_S, STATE_MAX };

    Enemy(GameObject& associated, int enemy_type = 1);

    ~Enemy() {}

    void Update(float dt);
    void RhythmUpdate()
    {
        num_beats++;

        if (!movement_allowed && num_beats > 1) {
            movement_allowed = true;
            num_beats = 0;
        }
    }
    void RhythmReset() {}
    void Render(Common::Layer layer) const {}

    Vec2 GetGridPosition()
    {
        return associated.GetGridPosition();
    }

    void MovementDenied()
    {
        movement_allowed = false;
    }

    Direction GetMovementDirection()
    {
        return movement_direction;
    }
    State GetState()
    {
        return state;
    }

    void SetAsHit()
    {
        associated.GetComponent<Interpol*>()->isHit = true;
        movement_allowed = false;
    }

    bool VerifyDeath(Alan* alan);

    void TakeDamage(int damage)
    {
        life_enemy -= damage;
    }

    void ShouldTakeDamage(Alan* alan);

    void IsSurrounded();

    bool movement_allowed = false;

  private:
    Direction movement_direction = Direction::LEFT;

    // 2<=range<=7
    int range, steps = 0;
    State state = State::IDLE_S;

    int num_beats = 0;

    int life_enemy;

    Vec2 tileMapPos;

    Sprite::SpriteState EState[State::STATE_MAX];
    InputManager& input;

    bool damage_taken = false;
};

#endif  // ENEMY_H
