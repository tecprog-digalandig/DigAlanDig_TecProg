#include "GridControl.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Enemy.h"

GridControl *GridControl::_instance = nullptr;

GridControl *GridControl::getInstance() {
    if (!_instance) _instance = new GridControl();
    return _instance;
}

int GridControl::testPath(Vec2 target, bool isAlan) {
    if ((target.x >= tileMap->GetWidth() || target.x < 0) ||
        (target.y >= tileMap->GetHeight() || target.y < 0)) {
        return WhatsThere::NONE;
    }

    int block = tileMap->At(target.x, target.y, TileMap::Layers::BLOCOS);

    if (isAlan) {
        if (VerifyEnemy(target)) {
            return WhatsThere::ENEMY;
        } else if (!block) {
            return WhatsThere::FREE;

        } else if (block) {
            blockLife = block;
            return WhatsThere::ROCK;
        }
        return WhatsThere::NONE;
    }

    if (alan.lock()) {
        if (target == alan.lock()->GetComponent<Alan *>()->getGridPosition())
            return WhatsThere::ALAN;
    }

    if (!block) {
        return WhatsThere::FREE;

    } else if (block) {
        return WhatsThere::ROCK;
    }

    return WhatsThere::NONE;
}

bool GridControl::VerifyEnemy(Vec2 target) {
    for (auto enemy : enemies) {
        if (enemy->GetComponent<Enemy *>()->getGridPosition() == target &&
            enemy->GetComponent<Enemy *>()->GetState() !=
                Enemy::State::WALKIN_S)
            return true;
    }

    return false;
}

void GridControl::CheckEnemyAlanCollision(bool isAlan) {
    for (auto enemy : enemies) {
        Vec2 alanPos = alan.lock()->GetComponent<Alan *>()->getGridPosition();
        Vec2 enemyPos = enemy->GetComponent<Enemy *>()->getGridPosition();

        if (alanPos.y == enemyPos.y &&
            (enemy->GetComponent<Enemy *>()->GetState() ==
                 Enemy::State::WALKIN_S ||
             alan.lock()->GetComponent<Alan *>()->getAction() ==
                 AlanActionControl::Action::walkin)) {
            if ((alanPos.x - enemyPos.x) == 1 &&
                (alan.lock()->GetComponent<Alan *>()->getMovementDirection() ==
                     AlanActionControl::Direction::left &&
                 enemy->GetComponent<Enemy *>()->getMovementDirection() ==
                     Enemy::Direction::right)) {
                if (isAlan) {
                    alan.lock()
                        ->GetComponent<AlanActionControl *>()
                        ->setMovementDirection(
                            AlanActionControl::Direction::NONE);
                } else {
                    enemy->GetComponent<Enemy *>()->SetAsHit();
                    enemy->GetComponent<Interpol *>()->target = {
                        enemy->gridPosition.x + 1, enemy->gridPosition.y};
                    alan.lock()->GetComponent<Alan *>()->takeDamage();
                }

                return;
            }
            if ((enemyPos.x - alanPos.x) == 1 &&
                (alan.lock()->GetComponent<Alan *>()->getMovementDirection() ==
                     AlanActionControl::Direction::right &&
                 enemy->GetComponent<Enemy *>()->getMovementDirection() ==
                     Enemy::Direction::left)) {
                if (isAlan) {
                    alan.lock()
                        ->GetComponent<AlanActionControl *>()
                        ->setMovementDirection(
                            AlanActionControl::Direction::NONE);
                } else {
                    enemy->GetComponent<Enemy *>()->SetAsHit();
                    enemy->GetComponent<Interpol *>()->target = {
                        enemy->gridPosition.x - 1, enemy->gridPosition.y};
                    alan.lock()->GetComponent<Alan *>()->takeDamage();
                }

                return;
            }
        }
    }
}