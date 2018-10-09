#include "Interpol.h"
#include "Enemy.h"
#include "Game.h"
#include "Sprite.h"

Interpol::Interpol(GameObject &associated) : Component(associated) {}

void Interpol::update(float dt) {
    Sprite *sprite = associated.GetComponent<Sprite *>();

    speed.x = 10 * dt * Game::GetInstance()->GetCurrentState().GetGridSize() /
              sprite->GetFrameCount();
    speed.y = 10 * dt * Game::GetInstance()->GetCurrentState().GetGridSize() /
              sprite->GetFrameCount();

    Vec2 newPos;

    if (isHit) {
        if (target.x > associated.gridPosition.x) {
            newPos = {
                target.x *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2};

        } else {
            newPos = {
                target.x * Game::GetInstance()->GetCurrentState().GetGridSize(),
                associated.gridPosition.y *
                        Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2};
        }
    } else
        newPos = {associated.gridPosition.x *
                          Game::GetInstance()->GetCurrentState().GetGridSize() -
                      Game::GetInstance()->GetCurrentState().GetGridSize() / 2,
                  associated.gridPosition.y *
                          Game::GetInstance()->GetCurrentState().GetGridSize() -
                      Game::GetInstance()->GetCurrentState().GetGridSize() / 2};

    if (associated.box.x != newPos.x) {
        if (abs(newPos.x - associated.box.x) < speed.x) {
            associated.box.x += (newPos.x - associated.box.x);
        } else if (associated.box.x < newPos.x) {
            associated.box.x += speed.x;
        } else {
            associated.box.x -= speed.x;
        }

        if (movementDone) movementDone = !movementDone;
    }

    if (associated.box.y != newPos.y) {
        if (abs(newPos.y - associated.box.y) < speed.y) {
            associated.box.y += (newPos.y - associated.box.y);
        } else if (associated.box.y < newPos.y) {
            associated.box.y += speed.y;
        } else {
            associated.box.y -= speed.y;
        }
        if (movementDone) movementDone = !movementDone;
    }

    if (associated.box.x == newPos.x && associated.box.y == newPos.y) {
        if (isHit) isHit = !isHit;
        if (!movementDone) movementDone = !movementDone;
    }
}