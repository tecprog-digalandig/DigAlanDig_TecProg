#include <assert.h>
#include "Interpol.h"
#include "Enemy.h"
#include "Game.h"
#include "Sprite.h"

/**
 * @brief Construct a new Interpol:: Interpol object
 * 
 * @param associated 
 */
Interpol::Interpol(GameObject &associated) : Component(associated) {}

/**
 * @brief update sprites of alan
 * 
 * @param dt 
 */
void Interpol::update(float dt) 
{
    Sprite *sprite = associated.GetComponent<Sprite *>();

    speed.x = 10 * dt * Game::GetInstance()->GetCurrentState().GetGridSize() /
              sprite->GetFrameCount();
    speed.y = 10 * dt * Game::GetInstance()->GetCurrentState().GetGridSize() /
              sprite->GetFrameCount();

    assert(speed.x > 0);          
    assert(speed.y > 0);
    Vec2 new_pos;

    if (is_hit) 
    {
        if (target.x > associated.gridPosition.x) 
        {
            new_pos = 
            {
                target.x *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2};

        } 
        else 
        {
            new_pos = 
            {
                target.x * Game::GetInstance()->GetCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2};
        }
    } 
    else
        new_pos = {associated.gridPosition.x *
                          Game::GetInstance()->GetCurrentState().GetGridSize() -
                      Game::GetInstance()->GetCurrentState().GetGridSize() / 2,
                  associated.gridPosition.y *
                          Game::GetInstance()->GetCurrentState().GetGridSize() -
                      Game::GetInstance()->GetCurrentState().GetGridSize() / 2};

    if (associated.box.x != new_pos.x) 
    {
        if (abs(new_pos.x - associated.box.x) < speed.x) 
        {
            associated.box.x += (new_pos.x - associated.box.x);
        } 
        else if (associated.box.x < new_pos.x) 
        {
            associated.box.x += speed.x;
        } 
        else 
        {
            associated.box.x -= speed.x;
        }

        if (movement_done) movement_done = !movement_done;
    }

    if (associated.box.y != new_pos.y) 
    {
        if (abs(new_pos.y - associated.box.y) < speed.y) 
        {
            associated.box.y += (new_pos.y - associated.box.y);
        } 
        else if (associated.box.y < new_pos.y) 
        {
            associated.box.y += speed.y;
        } 
        else 
        {
            associated.box.y -= speed.y;
        }
        if (movement_done) movement_done = !movement_done;
    }

    if (associated.box.x == new_pos.x && associated.box.y == new_pos.y) 
    {
        if (isHit) is_hit = !is_hit;
        if (!movement_done) movement_done = !movement_done;
    }
}