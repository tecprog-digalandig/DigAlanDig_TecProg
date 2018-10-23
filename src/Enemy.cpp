#include "Enemy.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Camera.h"
#include "EnemySpawn.h"
#include "Game.h"
#include "StageState.h"

Enemy::Enemy(GameObject &associated, int enemyType)
    : Component(associated), input(InputManager::getInstance()) {
    if (enemyType == 1) {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy1/IDLE.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy1/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy1/IDLE.png", 2, 2,
                                0.2};
    } else if (enemyType == 2) {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy2/IDLE.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy2/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy2/IDLE.png", 2, 2,
                                0.2};
    } else if (enemyType == 3) {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy3/IDLE.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy3/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy3/IDLE.png", 2, 2,
                                0.2};
    } else {
        EState[State::IDLE_S] = {"assets/img/enemies/enemy1/IDLE.png", 2, 2,
                                 -1};
        EState[State::WALKIN_S] = {"assets/img/enemies/enemy1/walkin.png", 2, 4,
                                   0.2};
        EState[State::DIE_S] = {"assets/img/enemies/enemy1/IDLE.png", 2, 2,
                                0.2};
    }

    Sprite *sprite =new Sprite(associated);
    Interpol *interpol = new Interpol(associated);
    associated.addComponent(sprite);
    associated.addComponent(interpol);
    sprite->Open(EState[state], Enemy::Direction::left);

    life_enemy = 3;
    range = enemyType;

    tileMapPos.x = associated.box.x;
    tileMapPos.y = associated.box.y;
}

bool Enemy::VerifyDeath(Alan *alan) {
    // Inimigo morre se:
    // 1. life_enemy <= 0
    if (life_enemy <= 0) {
        return true;
    }
    // 2. Alan cai em cima dele
    if (Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y),
            false) == GridControl::WhatsThere::ALAN) {
        return true;
    }
    // 3. Scroll da camera já passou da posição dele
    if (associated.getGridPosition().y <
        (Camera::pos.y / Game::getInstance()->getCurrentState().GetGridSize()) -
            3) {
        return true;
    }
    // 4. Espaço embaixo dele não é uma pedra
    if (Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            false) != GridControl::WhatsThere::ROCK) {
        return true;
    }

    return false;
}

void Enemy::ShouldTakeDamage(Alan *alan) {
    if (state != State::IDLE_S) return;

    if (Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            false) == GridControl::WhatsThere::ALAN &&
        alan->getMovementDirection() == AlanActionControl::Direction::right) {
        if (!damage_taken) {
            takeDamage(alan->getDamage());
            damage_taken = true;
        }
    } else if (Game::getInstance()->getGridControl()->testPath(
                   Vec2(associated.gridPosition.x + 1,
                        associated.gridPosition.y),
                   false) == GridControl::WhatsThere::ALAN &&
               alan->getMovementDirection() ==
                   AlanActionControl::Direction::left) {
        if (!damage_taken) {
            takeDamage(alan->getDamage());
            damage_taken = true;
        }
    } else {
        damage_taken = false;
    }
}

void Enemy::IsSurrounded() {
    if (Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            false) != GridControl::WhatsThere::FREE &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            false) != GridControl::WhatsThere::FREE)
        movementAllowed = false;
}

void Enemy::Update(float delta_time) {
    if (!Game::getInstance()->getGridControl()->GetAlan().lock() ||
        !associated.GetComponent<Interpol *>()->isMovementDone())
        return;

    Game::getInstance()->getGridControl()->CheckEnemyAlanCollision(false);
    if (associated.GetComponent<Interpol *>()->isHit) return;

    Sprite *sprite =associated.GetComponent<Sprite *>();
    Alan *alan = Game::getInstance()
                     ->getGridControl()
                     ->GetAlan()
                     .lock()
                     ->GetComponent<Alan *>();

    ShouldTakeDamage(alan);

    if (VerifyDeath(alan) || state == Enemy::State::DIE_S) {
        if (state != Enemy::State::DIE_S) {
            state = Enemy::State::DIE_S;
            sprite->Open(EState[state], Enemy::Direction::left);
        }
        if (sprite->frameTimePassed()) {
            Game::getInstance()->getGridControl()->DeleteEnemy(&associated);
            associated.RequestDelete();
        }
        return;
    }

    IsSurrounded();

    if (movementDirection == Enemy::Direction::left) {
        if (Game::getInstance()->getGridControl()->testPath(
                Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
                false) != GridControl::WhatsThere::FREE ||
            Game::getInstance()->getGridControl()->testPath(
                Vec2(associated.gridPosition.x - 1,
                     associated.gridPosition.y + 1),
                false) != GridControl::WhatsThere::ROCK) {
            movementAllowed = false;
            movementDirection = Enemy::Direction::right;
            steps = 0;
        }
    } else {
        if (Game::getInstance()->getGridControl()->testPath(
                Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
                false) != GridControl::WhatsThere::FREE ||
            Game::getInstance()->getGridControl()->testPath(
                Vec2(associated.gridPosition.x + 1,
                     associated.gridPosition.y + 1),
                false) != GridControl::WhatsThere::ROCK) {
            movementAllowed = false;
            movementDirection = Enemy::Direction::left;
            steps = 0;
        }
    }

    if (movementAllowed) {
        if (state != Enemy::State::WALKIN_S) {
            state = Enemy::State::WALKIN_S;
            sprite->Open(EState[state], movementDirection);
        }
        if (steps < range) {
            if (movementDirection == Enemy::Direction::left) {
                movementAllowed = false;
                steps++;
                associated.gridPosition.x--;

            } else {
                movementAllowed = false;
                steps++;
                associated.gridPosition.x++;
            }

        } else {
            if (movementDirection == Enemy::Direction::left) {
                movementDirection = Enemy::Direction::right;
            } else {
                movementDirection = Enemy::Direction::left;
            }
            steps = 0;
        }
    } else {
        if (state != Enemy::State::IDLE_S) {
            state = Enemy::State::IDLE_S;
            sprite->Open(EState[state], Enemy::Direction::left);
        }
    }
}
