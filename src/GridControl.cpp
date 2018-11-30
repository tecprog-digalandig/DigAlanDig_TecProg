/**
* @file GridControl.cpp
* @copyright 2018 Pedro H.
* @brief Class that implements methods that checks path and collision with enemys.
*/

#include "GridControl.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Enemy.h"
#include <assert.h>

GridControl *GridControl::_instance = nullptr;
assert(_instance == nullptr);

GridControl *GridControl::getInstance()
{
    if (!_instance)
    {
        _instance = new GridControl();
    }
    else
    {
        //Nothing to do
    }
    assert( _instance != nullptr);
    return _instance;
}

/**
* @brief Verify if a collision is with a enemy or block
* @param [in] target <parameter_description> Vec2 object
* @param [in] isAlan <parameter_description> bool variable
* @return if its an enemy, is free, nothing or a block in the way.
*/
int GridControl::TestPath(Vec2 target, bool isAlan)
{
    //Empty spaces in the game
    if ((target.x >= tileMap->GetWidth() || target.x < 0) ||
        (target.y >= tileMap->GetHeight() || target.y < 0))
    {
        return WhatsThere::NONE;
    }
    else
    {
        //Nothing to do
    }

    int block = tileMap->At(target.x, target.y, TileMap::Layers::BLOCOS);

    if (isAlan)
    {
        if (VerifyEnemy(target))
        {
            return WhatsThere::ENEMY;
        }
        else if (block)
        {
            blockLife = block;
            return WhatsThere::ROCK;
        }
        else if (!block)
        {
            return WhatsThere::FREE;
        }
        else
        {
            return WhatsThere::NONE;
        }
    }
    else
    {
        //Nothing to do
    }

    if (alan.lock())
    {
        if (target == alan.lock()->getComponent<Alan *>()->getGridPosition())
        {
            return WhatsThere::ALAN;
        }
        else
        {
            //Nothing to do
        }
    }

    if (block)
    {
        return WhatsThere::ROCK;
    }
    else if (!block)
    {
        return WhatsThere::FREE;
    }
    else
    {
        return WhatsThere::NONE;
    }
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
            else
            {
                //Nothing to do
            }
    }

    return false;
}

void checkIsAlan();

/**
* @brief Checks if Alan collide with an enemy and take damage.
* @param [in] isAlan <parameter_description> bool variable
*/
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
                checkIsAlan();
                return;
            }
            else
            {
                //Nothing to do
            }

            if ((enemyPos.x - alanPos.x) == 1 &&
                (alan.lock()->getComponent<Alan *>()->GetMovementDirection() ==
                AlanActionControl::Direction::RIGHT &&
                enemy->getComponent<Enemy *>()->GetMovementDirection() ==
                Enemy::Direction::LEFT))
            {
                checkIsAlan();
                return;
            }
            else
            {
                //Nothing to do
            }
        }
    }
}
void checkIsAlan()
{
    if (isAlan)
    {
        alan.lock()->getComponent<AlanActionControl *>()
        ->SetMovementDirection(AlanActionControl::Direction::NONE);
    }
    else
    {
        enemy->getComponent<Enemy *>()->SetAsHit();
        enemy->getComponent<Interpol *>()->target =
        {enemy->gridPosition.x + 1, enemy->gridPosition.y};

        alan.lock()->getComponent<Alan *>()->TakeDamage();
    }
}
