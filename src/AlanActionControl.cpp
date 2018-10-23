#include "AlanActionControl.h"
#include "Alan.h"
#include "AlanItemCount.h"
#include "Game.h"
#include "Interpol.h"
#include "Sprite.h"

bool AlanActionControl::shouldFall() 
{
    return grids_left ||
           ((Game::getInstance()->getGridControl()->testPath(
                 Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::FREE ||
             Game::getInstance()->getGridControl()->testPath(
                 Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::ENEMY));
}

void AlanActionControl::fallin(float delta_time) 
{
    if (grids_left > 0) grids_left--;
    associated.gridPosition.y++;
    associated.getComponent<Sprite *>()->timeElapsedReset();
}

bool AlanActionControl::isFree() 
{
    if (movement_direction == Direction::left &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    if (movement_direction == Direction::right &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    return false;
}

bool AlanActionControl::isBlock() 
{
    if (movement_direction == Direction::left &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) 
            {
        return true;
    }

    if (movement_direction == Direction::right &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) 
            {
        return true;
    }
    return false;
}

bool AlanActionControl::canClimb() 
{
    return input.keyDown(SDL_SCANCODE_A) && action != Action::WALK;
}

bool AlanActionControl::inClimbPosition(AlanAnimation *animation) 
{
    return (animation->getCurrentState() == AlanAnimation::State::climbin ||
            animation->getOldState() == AlanAnimation::State::climbin) &&
           animation->getCurrentState() != AlanAnimation::State::IDLE;
}

bool AlanActionControl::climbPathFree() 
{
    if (movement_direction == Direction::up &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    if (movement_direction == Direction::down &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            true) == GridControl::WhatsThere::FREE) 
            {
        return true;
    }

    return false;
}

bool AlanActionControl::isClimbDirectionleft(AlanAnimation *animation) 
{
    return (animation->getCurrentDirection() ==
                AlanAnimation::Direction::left ||
            animation->getOldDirection() == AlanAnimation::Direction::left) &&
           animation->getCurrentDirection() != AlanAnimation::Direction::right;
}

void AlanActionControl::update(float delta_time) 
{
    if (!associated.getComponent<Interpol *>()->isMovementDone()) return;

    Alan *alan = associated.getComponent<Alan *>();
    AlanAnimation *animation = associated.getComponent<AlanAnimation *>();
    TileMap *tile_map = Game::getInstance()->getCurrentState().tileMap;
    Sprite *sprite = associated.getComponent<Sprite *>();

    if (alan->getItemCount()
            ->getComponent<AlanItemCount *>()
            ->collectedAllItens()) {
        if (animation->getCurrentState() != AlanAnimation::State::dancin) 
        {
            animation->setAction(AlanAnimation::Transition::dance,
                                 AlanAnimation::Direction::left);
        }

        return;
    }

    if (alan->getHP() <= 0) 
    {
        if (animation->getCurrentState() != AlanAnimation::State::dead) 
        {
            animation->setAction(AlanAnimation::Transition::die,
                                 AlanAnimation::Direction::left);
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
        if (grids_left == 0) 
        {
            movement_direction = Direction::down;
            action = Action::fallin_var;
            int y = associated.gridPosition.y + 1;
            while (!tile_map->At(associated.gridPosition.x, y)) 
            {
                grids_left++;
                y++;
            }
            animation->setAction(AlanAnimation::Transition::fall,
                                 AlanAnimation::Direction::left);
        }

        fallin(delta_time);

        return;
    }

    if (animation->getCurrentState() == AlanAnimation::State::fallin_var) 
    {
        animation->setAction(AlanAnimation::Transition::floor,
                             AlanAnimation::Direction::left);
        action = Action::standin;
        movement_direction = Direction::NONE;
    }

    if (movement_direction == Direction::NONE) 
    {
        if (action != Action::climbin || !input.keyDown(SDL_SCANCODE_A)) 
        {
            animation->setAction(AlanAnimation::Transition::none_t,
                                 AlanAnimation::Direction::left);
            action = Action::standin;
        }

        return;
    }

    if (action != Action::WALK) 
    {
        action = Action::WALK;
    }
    // Up bate na pedra acima dele se houver
    if (movement_direction == Direction::up) 
    {
        if (Game::getInstance()->getGridControl()->testPath(
                Vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
                true) == GridControl::WhatsThere::ROCK) 
                {
            if (int item_type = Game::getInstance()->getGridControl()->isItem(
                    Vec2(associated.gridPosition.x,
                         associated.gridPosition.y - 1))) {
                tile_map->itemCollected(Vec2(associated.gridPosition.x,
                                            associated.gridPosition.y - 1),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(item_type);
            }

            if (!animation_on_going) 
            {
                animation->setAction(AlanAnimation::Transition::dig_t,
                                     AlanAnimation::Direction::up);
                animation_on_going = true;
            }
            if (sprite->frameTimePassed()) 
            {
                tile_map->getDamageGround(alan->getDamage(),
                                         Vec2(associated.gridPosition.x,
                                              associated.gridPosition.y - 1));
                movement_direction = Direction::NONE;
                animation_on_going = false;
            }

            return;
        } else 
        {
            movement_direction = Direction::NONE;
        }
        // Down bate na pedra embaixo dele
    } else if (movement_direction == Direction::down) 
    {
        if (int item_type = Game::getInstance()->getGridControl()->isItem(Vec2(
                associated.gridPosition.x, associated.gridPosition.y + 1))) 
                {
            tile_map->itemCollected(
                Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                TileMap::Layers::ITENS);
            alan->getItemCount()
                ->getComponent<AlanItemCount *>()
                ->itemCollected(item_type);

            animation->setAction(AlanAnimation::Transition::dig_t,
                                 AlanAnimation::Direction::down);

            tile_map->getDamageGround(
                alan->getDamage(),
                Vec2(associated.gridPosition.x, associated.gridPosition.y + 1));
            movement_direction = Direction::NONE;
            associated.gridPosition.y++;
        } else 
        {
            if (!animation_on_going) 
            {
                animation->setAction(AlanAnimation::Transition::dig_t,
                                     AlanAnimation::Direction::down);
                animation_on_going = true;
            }
            if (sprite->frameTimePassed()) 
            {
                tile_map->getDamageGround(alan->getDamage(),
                                         Vec2(associated.gridPosition.x,
                                              associated.gridPosition.y + 1));
                movement_direction = Direction::NONE;
                animation_on_going = false;
            }
        }
    } else if (movement_direction == Direction::left) 
    {
        // Testa se o valor do grid a esquerda é uma
        // pedra
        if (!isFree()) 
        {
            if (int item_type = Game::getInstance()->getGridControl()->isItem(
                    Vec2(associated.gridPosition.x - 1,
                         associated.gridPosition.y))) 
                         {
                tile_map->itemCollected(Vec2(associated.gridPosition.x - 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(item_type);
            }

            if (!animation_on_going) 
            {
                animation->setAction(AlanAnimation::Transition::dig_t,
                                     AlanAnimation::Direction::left);
                animation_on_going = true;
            }
            if (sprite->frameTimePassed()) 
            {
                if (isBlock()) 
                {
                    tile_map->getDamageGround(alan->getDamage(),
                                             Vec2(associated.gridPosition.x - 1,
                                                  associated.gridPosition.y));
                }
                movement_direction = Direction::NONE;
                animation_on_going = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::left);

            movement_direction = Direction::NONE;
            associated.gridPosition.x--;
        }
    } else 
    {
        // Mesmo processo anterior para a direita
        if (!isFree()) 
        {
            if (int item_type = Game::getInstance()->getGridControl()->isItem(
                    Vec2(associated.gridPosition.x + 1,
                         associated.gridPosition.y))) 
                         {
                tile_map->itemCollected(Vec2(associated.gridPosition.x + 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(item_type);
            }

            if (!animation_on_going) 
            {
                animation->setAction(AlanAnimation::Transition::dig_t,
                                     AlanAnimation::Direction::right);
                animation_on_going = true;
            }
            if (sprite->frameTimePassed()) 
            {
                if (isBlock()) 
                {
                    tile_map->getDamageGround(alan->getDamage(),
                                             Vec2(associated.gridPosition.x + 1,
                                                  associated.gridPosition.y));
                }
                movement_direction = Direction::NONE;
                animation_on_going = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::right);

            movement_direction = Direction::NONE;
            associated.gridPosition.x++;
            animation_on_going = false;
        }
    }
    if (animation->getCurrentState() == AlanAnimation::State::IDLE) 
    {
        animation_on_going = false;
    }
}
