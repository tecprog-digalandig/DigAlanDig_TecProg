#include "GridControl.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Enemy.h"

GridControl *GridControl::_instance = nullptr;

GridControl *GridControl::getInstance()
{
    if (!_instance) _instance = new GridControl();
    return _instance;
}

int GridControl::TestPath(Vec2 target, bool isAlan)
{
    if ((target.x >= tileMap->GetWidth() || target.x < 0) ||
        (target.y >= tileMap->GetHeight() || target.y < 0))
        {
            return WhatsThere::NONE;
        }

    int block = tileMap->At(target.x, target.y, TileMap::Layers::BLOCOS);

    if (isAlan)
    {
        if (VerifyEnemy(target))
        {
            return WhatsThere::ENEMY;
        }
        else if (!block)
        {
            return WhatsThere::FREE;
        }
        else if (block)
        {
            blockLife = block;
            return WhatsThere::ROCK;
        }

        return WhatsThere::NONE;
    }

    if (alan.lock())
    {
        if (target == alan.lock()->getComponent<Alan *>()->getGridPosition())
        {
            return WhatsThere::ALAN;
        }
    }

    if (!block)
    {
        return WhatsThere::FREE;
    }
    else if (block)
    {
        return WhatsThere::ROCK;
    }

    return WhatsThere::NONE;
}

bool GridControl::VerifyEnemy(Vec2 target)
{
    for (auto enemy : enemies)
    {
        if (enemy->getComponent<Enemy *>()->getGridPosition() == target &&
            enemy->getComponent<Enemy *>()->GetState() != Enemy::State::WALKIN_S)
            {
                return true;
            }
    }

    return false;
}

void GridControl::CheckEnemyAlanCollision(bool isAlan)
{
    for (auto enemy : enemies)
    {
        Vec2 alanPos = alan.lock()->getComponent<Alan *>()->getGridPosition();
        Vec2 enemyPos = enemy->getComponent<Enemy *>()->getGridPosition();

        if (alanPos.y == enemyPos.y && (enemy->getComponent<Enemy *>()->GetState() ==
            Enemy::State::WALKIN_S || alan.lock()->getComponent<Alan *>()->GetAction() ==
            AlanActionControl::Action::WALKIN))
        {
            if ((alanPos.x - enemyPos.x) == 1 &&
                (alan.lock()->getComponent<Alan *>()->GetMovementDirection() ==
                AlanActionControl::Direction::LEFT &&
                enemy->getComponent<Enemy *>()->GetMovementDirection() ==
                Enemy::Direction::RIGHT))
            {
                if (isAlan)
                {
                    alan.lock()
                        ->getComponent<AlanActionControl *>()
                        ->SetMovementDirection(
                            AlanActionControl::Direction::NONE);
                }
                else
                {
                    enemy->getComponent<Enemy *>()->SetAsHit();
                    enemy->getComponent<Interpol *>()->target =
                    {enemy->gridPosition.x + 1, enemy->gridPosition.y};

                    alan.lock()->getComponent<Alan *>()->TakeDamage();
                }

                return;
            }

            if ((enemyPos.x - alanPos.x) == 1 &&
                (alan.lock()->getComponent<Alan *>()->GetMovementDirection() ==
                AlanActionControl::Direction::RIGHT &&
                enemy->getComponent<Enemy *>()->GetMovementDirection() ==
                Enemy::Direction::LEFT))
            {
                if (isAlan)
                {
                    alan.lock()->getComponent<AlanActionControl *>()->
                    SetMovementDirection(AlanActionControl::Direction::NONE);
                }
                else
                {
                    enemy->getComponent<Enemy *>()->SetAsHit();
                    enemy->getComponent<Interpol *>()->target =
                    {enemy->gridPosition.x - 1, enemy->gridPosition.y};

                    alan.lock()->getComponent<Alan *>()->TakeDamage();
                }

                return;
            }
        }
    }
}
