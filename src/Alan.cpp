#include "Alan.h"
#include <algorithm>
#include "AlanAnimation.h"
#include "Interpol.h"
#include "Sprite.h"

// Constructor of Alan's class.
Alan::Alan(GameObject &associated)
    : Component(associated), input(InputManager::GetInstance()) 
    {}

// Method that gets movement direction.
void Alan::getMovement() 
{
    if (moved ||
        associated.getComponent<AlanActionControl *>()->getMovementDirection())
        return;
    if (input.actionPress(input.DIG_UP)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::up);
        moved = true;
    }
    if (input.actionPress(input.DIG_DOWN)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::down);
        moved = true;
    }
    if (input.actionPress(input.DIG_LEFT)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::left);
        moved = true;
    }
    if (input.actionPress(input.DIG_RIGHT)) 
    {
        associated.getComponent<AlanActionControl *>()->setMovementDirection(
            AlanActionControl::Direction::right);
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

// Method that updates Alan on grid.
void Alan::update(float dt) 
{
    if (max_position < std::max(associated.gridPosition.y + 4, 7.0)) 
    {
        max_position = std::max(associated.gridPosition.y + 4, 7.0);
    }

    getMovement();
}
