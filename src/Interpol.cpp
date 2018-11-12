#include "Interpol.h"
#include "Enemy.h"
#include "Game.h"
#include "Sprite.h"

Interpol::Interpol(GameObject &associated) : Component(associated) {}

<<<<<<< HEAD
void Interpol::Update(float delta_time) {
    Sprite *sprite =associated.GetComponent<Sprite *>();
=======
void Interpol::update(float dt) {
    Sprite *sprite = associated.GetComponent<Sprite *>();
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9

    speed.x = 10 * delta_time * Game::getInstance()->getCurrentState().GetGridSize() /
              sprite->GetFrameCount();
    speed.y = 10 * delta_time * Game::getInstance()->getCurrentState().GetGridSize() /
              sprite->GetFrameCount();

    Vec2 new_pos;

    if (is_hit)
    {
        if (target.x > associated.gridPosition.x)
        {
            new_pos = {
                target.x *
                        Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2};

        } else {
            new_pos = {
                target.x * Game::getInstance()->getCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2};
        }
    } else
        new_pos = {associated.gridPosition.x *
                          Game::getInstance()->getCurrentState().GetGridSize() -
                      Game::getInstance()->getCurrentState().GetGridSize() / 2,
                  associated.gridPosition.y *
                          Game::getInstance()->getCurrentState().GetGridSize() -
                      Game::getInstance()->getCurrentState().GetGridSize() / 2};

    if (associated.box.x != new_pos.x) {
        if (abs(new_pos.x - associated.box.x) < speed.x) {
            associated.box.x += (new_pos.x - associated.box.x);
        } else if (associated.box.x < new_pos.x) {
            associated.box.x += speed.x;
        }
        else
        {
            associated.box.x -= speed.x;
        }

        if (movement_done) { movement_done = !movement_done };
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
        if (movement_done) { movement_done = !movement_done };
    }

    if (associated.box.x == new_pos.x && associated.box.y == new_pos.y)
    {
        if (is_hit) { is_hit = !is_hit };
        if (!movement_done) { movement_done = !movement_done };
    }
}
