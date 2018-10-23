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
    enum Direction { left = 0, right };
    enum State { NONE_S = 0, IDLE_S, WALKIN_S, DIE_S, STATE_MAX };

    Enemy(GameObject& associated, int enemyType = 1);

    ~Enemy() {}

    void Update(float delta_time);
    void rhythmUpdate() {
        numBeats++;

        if (!movementAllowed && numBeats > 1) {
            movementAllowed = true;
            numBeats = 0;
        }
    }
    void rhythmReset() {}
    void render(Common::Layer layer) const {}

    Vec2 getGridPosition() { return associated.getGridPosition(); }

    void MovementDenied() { movementAllowed = false; }

    Direction getMovementDirection() { return movementDirection; }
    State GetState() { return state; }

    void SetAsHit() {
        associated.GetComponent<Interpol*>()->isHit = true;
        movementAllowed = false;
    }

    bool VerifyDeath(Alan* alan);

    void takeDamage(int damage) { life_enemy = damage; }
    void ShouldTakeDamage(Alan* alan);

    void IsSurrounded();

    bool movementAllowed = false;

  private:
    Direction movementDirection = Direction::left;

    // 2<=range<=7
    int range, steps = 0;
    State state = State::IDLE_S;

    int numBeats = 0;

    int hp, life_enemy;

    Vec2 tileMapPos;

    Sprite::SpriteState EState[State::STATE_MAX];
    InputManager& input;

    bool damage_taken = false;
};

#endif  // ENEMY_H
