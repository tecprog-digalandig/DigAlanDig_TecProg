#include "GridControl.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Enemy.h"

GridControl *GridControl::_instance = nullptr;

GridControl *GridControl::GetInstance()
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
        if (target == alan.lock()->GetComponent<Alan *>()->GetGridPosition())
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
        if (enemy->GetComponent<Enemy *>()->GetGridPosition() == target &&
            enemy->GetComponent<Enemy *>()->GetState() != Enemy::State::WALKIN_S)
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
        Vec2 alanPos = alan.lock()->GetComponent<Alan *>()->GetGridPosition();
        Vec2 enemyPos = enemy->GetComponent<Enemy *>()->GetGridPosition();

        if (alanPos.y == enemyPos.y && (enemy->GetComponent<Enemy *>()->GetState() ==
            Enemy::State::WALKIN_S || alan.lock()->GetComponent<Alan *>()->GetAction() ==
            AlanActionControl::Action::WALKIN))
        {
            if ((alanPos.x - enemyPos.x) == 1 &&
                (alan.lock()->GetComponent<Alan *>()->GetMovementDirection() ==
                AlanActionControl::Direction::LEFT &&
                enemy->GetComponent<Enemy *>()->GetMovementDirection() ==
                Enemy::Direction::RIGHT))
            {
                if (isAlan)
                {
                    alan.lock()
                        ->GetComponent<AlanActionControl *>()
                        ->SetMovementDirection(
                            AlanActionControl::Direction::NONE);
                }
                else
                {
                    enemy->GetComponent<Enemy *>()->SetAsHit();
                    enemy->GetComponent<Interpol *>()->target =
                    {enemy->gridPosition.x + 1, enemy->gridPosition.y};

                    alan.lock()->GetComponent<Alan *>()->TakeDamage();
                }

                return;
            }

            if ((enemyPos.x - alanPos.x) == 1 &&
                (alan.lock()->GetComponent<Alan *>()->GetMovementDirection() ==
                AlanActionControl::Direction::RIGHT &&
                enemy->GetComponent<Enemy *>()->GetMovementDirection() ==
                Enemy::Direction::LEFT))
            {
                if (isAlan)
                {
                    alan.lock()->GetComponent<AlanActionControl *>()->
                    SetMovementDirection(AlanActionControl::Direction::NONE);
                }
                else
                {
                    enemy->GetComponent<Enemy *>()->SetAsHit();
                    enemy->GetComponent<Interpol *>()->target =
                    {enemy->gridPosition.x - 1, enemy->gridPosition.y};

                    alan.lock()->GetComponent<Alan *>()->TakeDamage();
                }

                return;
            }
        }
    }
}
