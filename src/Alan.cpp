#include "Alan.h"
#include <algorithm>
#include "AlanAnimation.h"
#include "Interpol.h"
#include "Sprite.h"

Alan::alan(GameObject &associated)
    : Component(associated), input(InputManager::GetInstance()) 
    {}

// Direção do movimento
void Alan::getMovement() 
{
    if (moved ||
        associated.getComponent<AlanActionControl *>()->getMovementDirection())
        return;
    //
    if (input.actionPress(input.DIG_UP)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::UP);
        moved = true;
    }
    if (input.actionPress(input.DIG_DOWN)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::DOWN);
        moved = true;
    }
    if (input.actionPress(input.DIG_LEFT)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::LEFT);
        moved = true;
    }
    if (input.actionPress(input.DIG_RIGHT)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::RIGHT);
        moved = true;
    }

    if (associated.getComponent<AlanActionControl *>()
            ->getMovementDirection()) 
            {
        float duty = 0.6;
        input.move();
        if (std::abs(input.getDeltaRhythm()) < duty) 
        {
            std::cout << "\n\nHit: " << input.getDeltaRhythm() << "\n\n";
            Game::getInstance()->combo++;
        } else 
        {
            Camera::shake();
            Game::getInstance()->combo = 0;
            std::cout << "\n\nMiss: " << input.getDeltaRhythm() << "\n\n";
        }
    }

    Game::getInstance()->getGridControl()->checkEnemyAlanCollision(true);
}

void Alan::update(float dt) 
{
    if (maxPosition < std::max(associated.gridPosition.y + 4, 7.0)) 
    {
        maxPosition = std::max(associated.gridPosition.y + 4, 7.0);
    }

    getMovement();
}
