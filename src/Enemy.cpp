#include "Enemy.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Camera.h"
#include "EnemySpawn.h"
#include "Game.h"
#include "StageState.h"
#include <assert.h>

Enemy::Enemy(GameObject &associated, int enemy_type)
    : Component(associated), input(InputManager::GetInstance()) {
    if (enemy_type == 1) {
        assert(enemy_type == 1);
        EState[State::IDLE_S] = {"assets/img/enemies/enemy1/idle.png", 2, 2,
                                 -1};                         
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy1/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy1/idle.png", 2, 2,
                                0.2};
    } else if (enemy_type == 2) {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy2/idle.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy2/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy2/idle.png", 2, 2,
                                0.2};
    } else if (enemy_type == 3) {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy3/idle.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy3/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy3/idle.png", 2, 2,
                                0.2};
    } else {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy1/idle.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy1/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy1/idle.png", 2, 2,
                                0.2};
    }

    Sprite *sprite = new Sprite(associated);
    Interpol *interpol = new Interpol(associated);
    associated.AddComponent(sprite);
    associated.AddComponent(interpol);
    sprite->Open(EState[state], Enemy::Direction::LEFT);

    life_enemy = 3;
    assert(life_enemy == 3);
    range = enemy_type;

    tileMapPos.x = associated.box.x;
    tileMapPos.y = associated.box.y;
}

bool Enemy::VerifyDeath(Alan *alan)
{
    // Enemy dies if:
    // 1. life_enemy <= 0
    if (life_enemy <= 0) {
        return true;
    }
    // Modulo 5 - Clareza
    // 2. Alan falls on top of him
    if (Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y),
            false) == GridControl::WhatsThere::ALAN) {
        return true;
    }
    // Modulo 5 - Clareza
    // 3. Camera Scroll has already passed its position
    if (associated.GetGridPosition().y <
        (Camera::pos.y / Game::GetInstance()->GetCurrentState().GetGridSize()) -
            3) {
        return true;
    }
    // Modulo 5 - Clareza
    // 4. Space below it is not a stone
    if (Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            false) != GridControl::WhatsThere::ROCK) {
        return true;
    }

    return false;
}

void Enemy::ShouldTakeDamage(Alan *alan)
{
    if (state != State::IDLE_S) return;

    if (Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            false) == GridControl::WhatsThere::ALAN &&
        alan->GetMovementDirection() == AlanActionControl::Direction::RIGHT) {
        if (!damage_taken) {
            TakeDamage(alan->GetDamage());
            damage_taken = true;
        }
    } else if (Game::GetInstance()->GetGridControl()->TestPath(
                   Vec2(associated.gridPosition.x + 1,
                        associated.gridPosition.y),
                   false) == GridControl::WhatsThere::ALAN &&
               alan->GetMovementDirection() ==
                   AlanActionControl::Direction::LEFT) {
        if (!damage_taken) {
            TakeDamage(alan->GetDamage());
            damage_taken = true;
        }
    } else {
        damage_taken = false;
    }
}

void Enemy::IsSurrounded()
{
    if (Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            false) != GridControl::WhatsThere::FREE &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            false) != GridControl::WhatsThere::FREE)
        movement_allowed = false;
}
// Modulo 5 - Tipos descritivos. Const
void Enemy::update(const float dt)
{
    if (!Game::GetInstance()->GetGridControl()->GetAlan().lock() ||
        !associated.GetComponent<Interpol *>()->IsMovementDone())
        return;

    Game::GetInstance()->GetGridControl()->CheckEnemyAlanCollision(false);
    if (associated.GetComponent<Interpol *>()->isHit) return;

    Sprite *sprite = associated.GetComponent<Sprite *>();
    Alan *alan = Game::GetInstance()
                     ->GetGridControl()
                     ->GetAlan()
                     .lock()
                     ->GetComponent<Alan *>();

    ShouldTakeDamage(alan);

    if (VerifyDeath(alan) || state == Enemy::State::DIE_S) {
        if (state != Enemy::State::DIE_S) {
            state = Enemy::State::DIE_S;
            sprite->Open(EState[state], Enemy::Direction::LEFT);
        }
        if (sprite->FrameTimePassed()) {
            Game::GetInstance()->GetGridControl()->DeleteEnemy(&associated);
            associated.RequestDelete();
        }
        return;
    }

    IsSurrounded();

    if (movement_direction == Enemy::Direction::LEFT) {
        if (Game::GetInstance()->GetGridControl()->TestPath(
                Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
                false) != GridControl::WhatsThere::FREE ||
            Game::GetInstance()->GetGridControl()->TestPath(
                Vec2(associated.gridPosition.x - 1,
                     associated.gridPosition.y + 1),
                false) != GridControl::WhatsThere::ROCK) {
            movement_allowed = false;
            movement_direction = Enemy::Direction::RIGHT;
            steps = 0;
        }
    } else {
        if (Game::GetInstance()->GetGridControl()->TestPath(
                Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
                false) != GridControl::WhatsThere::FREE ||
            Game::GetInstance()->GetGridControl()->TestPath(
                Vec2(associated.gridPosition.x + 1,
                     associated.gridPosition.y + 1),
                false) != GridControl::WhatsThere::ROCK) {
            movement_allowed = false;
            movement_direction = Enemy::Direction::LEFT;
            steps = 0;
        }
    }

    if (movement_allowed) {
        if (state != Enemy::State::WALKIN_S) {
            state = Enemy::State::WALKIN_S;
            sprite->Open(EState[state], movement_direction);
        }
        if (steps < range) {
            if (movement_direction == Enemy::Direction::LEFT) {
                movement_allowed = false;
                steps++;
                associated.gridPosition.x--;

            } else {
                movement_allowed = false;
                steps++;
                associated.gridPosition.x++;
            }

        } else {
            if (movement_direction == Enemy::Direction::LEFT) {
                movement_direction = Enemy::Direction::RIGHT;
            } else {
                movement_direction = Enemy::Direction::LEFT;
            }
            steps = 0;
        }
    } else {
        if (state != Enemy::State::IDLE_S) {
            state = Enemy::State::IDLE_S;
            sprite->Open(EState[state], Enemy::Direction::LEFT);
        }
    }
}