#include "AlanActionControl.h"
#include "Alan.h"
#include "AlanItemCount.h"
#include "Game.h"
#include "Interpol.h"
#include "Sprite.h"

bool AlanActionControl::shouldFall() 
{
    return gridsLeft ||
           ((Game::getInstance()->getGridControl()->testPath(
                 vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::FREE ||
             Game::getInstance()->getGridControl()->testPath(
                 vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::ENEMY));
}

void AlanActionControl::fallin(float dt) 
{
    if (gridsLeft > 0) gridsLeft--;
    associated.gridPosition.y++;
    associated.getComponent<Sprite *>()->timeElapsedReset();
}

bool AlanActionControl::isFree() 
{
    if (movementDirection == Direction::LEFT &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    if (movementDirection == Direction::RIGHT &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    return false;
}

bool AlanActionControl::isBlock() 
{
    if (movementDirection == Direction::LEFT &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) 
            {
        return true;
    }

    if (movementDirection == Direction::RIGHT &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) 
            {
        return true;
    }
    return false;
}

bool AlanActionControl::canClimb() 
{
    return input.keyDown(SDL_SCANCODE_A) && action != Action::WALKIN;
}

bool AlanActionControl::inClimbPosition(AlanAnimation *animation) 
{
    return (animation->getCurrentState() == AlanAnimation::State::CLIMBIN ||
            animation->getOldState() == AlanAnimation::State::CLIMBIN) &&
           animation->getCurrentState() != AlanAnimation::State::IDLE;
}

bool AlanActionControl::climbPathFree() 
{
    if (movementDirection == Direction::UP &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    if (movementDirection == Direction::DOWN &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    return false;
}

bool AlanActionControl::isClimbDirectionLeft(AlanAnimation *animation) 
{
    return (animation->getCurrentDirection() ==
                AlanAnimation::Direction::LEFT ||
            animation->getOldDirection() == AlanAnimation::Direction::LEFT) &&
           animation->getCurrentDirection() != AlanAnimation::Direction::RIGHT;
}

void AlanActionControl::update(float dt) 
{
    if (!associated.getComponent<Interpol *>()->isMovementDone()) return;

    Alan *alan = associated.getComponent<Alan *>();
    AlanAnimation *animation = associated.getComponent<AlanAnimation *>();
    TileMap *tileMap = Game::getInstance()->getCurrentState().tileMap;
    Sprite *sprite = associated.getComponent<Sprite *>();

    if (alan->getItemCount()
            ->getComponent<AlanItemCount *>()
            ->collectedAllItens()) {
        if (animation->getCurrentState() != AlanAnimation::State::DANCIN) 
        {
            animation->setAction(AlanAnimation::Transition::DANCE,
                                 AlanAnimation::Direction::LEFT);
        }

        return;
    }

    if (alan->getHP() <= 0) 
    {
        if (animation->getCurrentState() != AlanAnimation::State::DEAD) 
        {
            animation->SetAction(AlanAnimation::Transition::DIE,
                                 AlanAnimation::Direction::LEFT);
        }

        if (sprite->frameTimePassed()) 
        {
            Game::getInstance()->combo = 0;
        }
        return;
    }

    // Testa se a marmota deve "cair" ou ficar na posição atual
    if (shouldFall()) 
    {
        if (gridsLeft == 0) 
        {
            movementDirection = Direction::DOWN;
            action = Action::FALLIN;
            int y = associated.gridPosition.y + 1;
            while (!tileMap->at(associated.gridPosition.x, y)) 
            {
                gridsLeft++;
                y++;
            }
            animation->setAction(AlanAnimation::Transition::FALL,
                                 AlanAnimation::Direction::LEFT);
        }

        fallin(dt);

        return;
    }

    if (animation->getCurrentState() == AlanAnimation::State::FALLIN) 
    {
        animation->setAction(AlanAnimation::Transition::FLOOR,
                             AlanAnimation::Direction::LEFT);
        action = Action::STANDIN;
        movementDirection = Direction::NONE;
    }

    if (movementDirection == Direction::NONE) 
    {
        if (action != Action::CLIMBING || !input.keyDown(SDL_SCANCODE_A)) 
        {
            animation->setAction(AlanAnimation::Transition::NONE_T,
                                 AlanAnimation::Direction::LEFT);
            action = Action::STANDIN;
        }

        return;
    }

    if (action != Action::WALKIN) 
    {
        action = Action::WALKIN;
    }
    // Up bate na pedra acima dele se houver
    if (movementDirection == Direction::UP) 
    {
        if (Game::getInstance()->getGridControl()->testPath(
                vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
                true) == GridControl::WhatsThere::ROCK) 
                {
            if (int itemType = Game::getInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x,
                         associated.gridPosition.y - 1))) {
                tileMap->itemCollected(vec2(associated.gridPosition.x,
                                            associated.gridPosition.y - 1),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(itemType);
            }

            if (!animationOnGoing) 
            {
                animation->setAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::UP);
                animationOnGoing = true;
            }
            if (sprite->frameTimePassed()) 
            {
                tileMap->getDamageGround(alan->getDamage(),
                                         vec2(associated.gridPosition.x,
                                              associated.gridPosition.y - 1));
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

            return;
        } else 
        {
            movementDirection = Direction::NONE;
        }
        // Down bate na pedra embaixo dele
    } else if (movementDirection == Direction::DOWN) 
    {
        if (int itemType = Game::getInstance()->getGridControl()->isItem(vec2(
                associated.gridPosition.x, associated.gridPosition.y + 1))) 
                {
            tileMap->itemCollected(
                vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                TileMap::Layers::ITENS);
            alan->getItemCount()
                ->getComponent<AlanItemCount *>()
                ->itemCollected(itemType);

            animation->setAction(AlanAnimation::Transition::DIG_T,
                                 AlanAnimation::Direction::DOWN);

            tileMap->getDamageGround(
                alan->getDamage(),
                vec2(associated.gridPosition.x, associated.gridPosition.y + 1));
            movementDirection = Direction::NONE;
            associated.gridPosition.y++;
        } else 
        {
            if (!animationOnGoing) 
            {
                animation->setAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::DOWN);
                animationOnGoing = true;
            }
            if (sprite->frameTimePassed()) 
            {
                tileMap->getDamageGround(alan->getDamage(),
                                         vec2(associated.gridPosition.x,
                                              associated.gridPosition.y + 1));
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }
        }
    } else if (movementDirection == Direction::LEFT) 
    {
        // Testa se o valor do grid a esquerda é uma
        // pedra
        if (!isFree()) 
        {
            if (int itemType = Game::getInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x - 1,
                         associated.gridPosition.y))) 
                         {
                tileMap->itemCollected(Vec2(associated.gridPosition.x - 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(itemType);
            }

            if (!animationOnGoing) 
            {
                animation->setAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::LEFT);
                animationOnGoing = true;
            }
            if (sprite->frameTimePassed()) 
            {
                if (isBlock()) 
                {
                    tileMap->getDamageGround(alan->getDamage(),
                                             vec2(associated.gridPosition.x - 1,
                                                  associated.gridPosition.y));
                }
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::LEFT);

            movementDirection = Direction::NONE;
            associated.gridPosition.x--;
        }
    } else 
    {
        // Mesmo processo anterior para a direita
        if (!isFree()) 
        {
            if (int itemType = Game::GetInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x + 1,
                         associated.gridPosition.y))) 
                         {
                tileMap->itemCollected(Vec2(associated.gridPosition.x + 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(itemType);
            }

            if (!animationOnGoing) 
            {
                animation->setAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::RIGHT);
                animationOnGoing = true;
            }
            if (sprite->frameTimePassed()) 
            {
                if (isBlock()) 
                {
                    tileMap->getDamageGround(alan->getDamage(),
                                             vec2(associated.gridPosition.x + 1,
                                                  associated.gridPosition.y));
                }
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::RIGHT);

            movementDirection = Direction::NONE;
            associated.gridPosition.x++;
            animationOnGoing = false;
        }
    }
    if (animation->getCurrentState() == AlanAnimation::State::IDLE) 
    {
        animationOnGoing = false;
    }
}
