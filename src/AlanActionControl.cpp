#include "AlanActionControl.h"
#include "Alan.h"
#include "AlanItemCount.h"
#include "Game.h"
#include "Interpol.h"
#include "Sprite.h"

// Check if Alan should fall or not.
bool AlanActionControl::shouldFall() 
{
    return grids_left ||
           ((Game::getInstance()->getGridControl()->testPath(
                 vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::FREE ||
             Game::getInstance()->getGridControl()->testPath(
                 vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::ENEMY));
}

// Method to control fallin.
void AlanActionControl::fallin(float dt) 
{
    if (grids_left > 0) grids_left--;
    associated.gridPosition.y++;
    associated.getComponent<Sprite *>()->timeElapsedReset();
}

// Check if movement direction is free.
bool AlanActionControl::isFree() 
{
    if (movement_direction == Direction::left &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::free) 
            {
        return true;
    }

    if (movement_direction == Direction::right &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::free) 
            {
        return true;
    }

    return false;
}

// Check if movement direction is blocked.
bool AlanActionControl::isBlock() 
{
    if (movement_direction == Direction::left &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::rock) 
            {
        return true;
    }

    if (movement_direction == Direction::right &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::rock) 
            {
        return true;
    }
    return false;
}

// Check if the player is able to climb.
bool AlanActionControl::canClimb() 
{
    return input.keyDown(sdl_scancode_a) && action != Action::walkin;
}

//Check player climb position.
bool AlanActionControl::inClimbPosition(AlanAnimation *animation) 
{
    return (animation->getCurrentState() == AlanAnimation::State::climbin ||
            animation->getOldState() == AlanAnimation::State::climbin) &&
           animation->getCurrentState() != AlanAnimation::State::idle;
}

bool AlanActionControl::climbPathFree() 
{
    if (movement_direction == Direction::up &&
        Game::getInstance()->getGridControl()->testPath(
            vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
            true) == GridControl::WhatsThere::free) 
            {
        return true;
    }

    if (movement_direction == Direction::down &&
        Game::getInstance()->getGridControl()->testPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            true) == GridControl::WhatsThere::free) 
            {
        return true;
    }

    return false;
}

bool AlanActionControl::isClimbDirectionLeft(AlanAnimation *animation) 
{
    return (animation->getCurrentDirection() ==
                AlanAnimation::Direction::left ||
            animation->getOldDirection() == AlanAnimation::Direction::left) &&
           animation->getCurrentDirection() != AlanAnimation::Direction::right;
}

// Updates player position.
void AlanActionControl::update(float dt) 
{
    if (!associated.getComponent<Interpol *>()->isMovementDone()) return;

    Alan *alan = associated.getComponent<Alan *>();
    AlanAnimation *animation = associated.getComponent<AlanAnimation *>();
    TileMap *tile_map = Game::getInstance()->getCurrentState().tile_map;
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
            animation->SetAction(AlanAnimation::Transition::die,
                                 AlanAnimation::Direction::left);
        }

        if (sprite->frameTimePassed()) 
        {
            Game::getInstance()->combo = 0;
        }
        return;
    }

    // Checks if the player must fall or not.
    if (shouldFall()) 
    {
        if (grids_left == 0) 
        {
            movement_direction = Direction::down;
            action = Action::fallin;
            int y = associated.gridPosition.y + 1;
            while (!tile_map->at(associated.gridPosition.x, y)) 
            {
                grids_left++;
                y++;
            }
            animation->setAction(AlanAnimation::Transition::fall,
                                 AlanAnimation::Direction::left);
        }

        fallin(dt);

        return;
    }

    if (animation->getCurrentState() == AlanAnimation::State::fallin) 
    {
        animation->setAction(AlanAnimation::Transition::floor,
                             AlanAnimation::Direction::left);
        action = Action::standin;
        movement_direction = Direction::none;
    }

    if (movement_direction == Direction::none) 
    {
        if (action != Action::climbin || !input.keyDown(SDL_SCANCODE_A)) 
        {
            animation->setAction(AlanAnimation::Transition::none_t,
                                 AlanAnimation::Direction::left);
            action = Action::standin;
        }

        return;
    }

    if (action != Action::walkin) 
    {
        action = Action::walkin;
    }
    // Hits the rock above him.
    if (movement_direction == Direction::up) 
    {
        if (Game::getInstance()->getGridControl()->testPath(
                vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
                true) == GridControl::WhatsThere::rock) 
                {
            if (int itemType = Game::getInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x,
                         associated.gridPosition.y - 1))) {
                tileMap->itemCollected(vec2(associated.gridPosition.x,
                                            associated.gridPosition.y - 1),
                                       TileMap::Layers::itens);
                alan->getItemCount()
                    ->getComponent<AlanItemCount *>()
                    ->itemCollected(item_type);
            }

            if (!animationOnGoing) 
            {
                animation->setAction(AlanAnimation::Transition::dig_t,
                                     AlanAnimation::Direction::up);
                animation_on_going = true;
            }
            if (sprite->frameTimePassed()) 
            {
                tile_map->getDamageGround(alan->getDamage(),
                                         vec2(associated.gridPosition.x,
                                              associated.gridPosition.y - 1));
                movement_direction = Direction::none;
                animation_on_going = false;
            }

            return;
        } else 
        {
            movement_direction = Direction::none;
        }
        // Hits the rock below him.
    } else if (movement_direction == Direction::down) 
    {
        if (int item_type = Game::getInstance()->getGridControl()->isItem(vec2(
                associated.gridPosition.x, associated.gridPosition.y + 1))) 
                {
            tile_map->itemCollected(
                vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                TileMap::Layers::itens);
            alan->getItemCount()
                ->getComponent<AlanItemCount *>()
                ->itemCollected(item_type);

            animation->setAction(AlanAnimation::Transition::dig_t,
                                 AlanAnimation::Direction::down);

            tile_map->getDamageGround(
                alan->getDamage(),
                vec2(associated.gridPosition.x, associated.gridPosition.y + 1));
            movement_direction = Direction::none;
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
                                         vec2(associated.gridPosition.x,
                                              associated.gridPosition.y + 1));
                movement_direction = Direction::none;
                animation_on_going = false;
            }
        }
    } else if (movement_direction == Direction::left) 
    {
        // Checks if left grid value is a rock.
        if (!isFree()) 
        {
            if (int item_type = Game::getInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x - 1,
                         associated.gridPosition.y))) 
                         {
                tile_map->itemCollected(Vec2(associated.gridPosition.x - 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::itens);
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
                                             vec2(associated.gridPosition.x - 1,
                                                  associated.gridPosition.y));
                }
                movement_direction = Direction::none;
                animation_on_going = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::walk,
                                 AlanAnimation::Direction::left);

            movement_direction = Direction::none;
            associated.gridPosition.x--;
        }
    } else 
    {
        // Checks if right grid value is a rock.
        if (!isFree()) 
        {
            if (int itemType = Game::GetInstance()->getGridControl()->isItem(
                    vec2(associated.gridPosition.x + 1,
                         associated.gridPosition.y))) 
                         {
                tile_map->itemCollected(Vec2(associated.gridPosition.x + 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::itens);
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
                                             vec2(associated.gridPosition.x + 1,
                                                  associated.gridPosition.y));
                }
                movement_direction = Direction::none;
                animation_on_going = false;
            }

        } else 
        {
            animation->setAction(AlanAnimation::Transition::walk,
                                 AlanAnimation::Direction::right);

            movement_direction = Direction::none;
            associated.gridPosition.x++;
            animation_on_going = false;
        }
    }
    if (animation->getCurrentState() == AlanAnimation::State::idle) 
    {
        animation_on_going = false;
    }
}
