#include "Alan.h"
#include <algorithm>
#include "AlanAnimation.h"
#include "Interpol.h"
#include "Sprite.h"

Alan::Alan(GameObject &associated)
    : Component(associated), input(InputManager::GetInstance()) {}

// Direção do movimento
void Alan::GetMovement() {
    if (moved ||
        associated.GetComponent<AlanActionControl *>()->GetMovementDirection())
        return;
    //
    if (input.ActionPress(input.DIG_UP)) {
        associated.GetComponent<AlanActionControl *>()->SetMovementDirection(
            AlanActionControl::Direction::UP);
        moved = true;
    }
    if (input.ActionPress(input.DIG_DOWN)) {
        associated.GetComponent<AlanActionControl *>()->SetMovementDirection(
            AlanActionControl::Direction::DOWN);
        moved = true;
    }
    if (input.ActionPress(input.DIG_LEFT)) {
        associated.GetComponent<AlanActionControl *>()->SetMovementDirection(
            AlanActionControl::Direction::LEFT);
        moved = true;
    }
    if (input.ActionPress(input.DIG_RIGHT)) {
        associated.GetComponent<AlanActionControl *>()->SetMovementDirection(
            AlanActionControl::Direction::RIGHT);
        moved = true;
    }

    if (associated.GetComponent<AlanActionControl *>()
            ->GetMovementDirection()) {
        float duty = 0.4;
        if (std::abs(input.GetDeltaRhythm()) > duty) {
            std::cout << "\n\nHit: " << input.GetDeltaRhythm() << "\n\n";
            Game::GetInstance()->combo++;
        } else {
            Camera::Shake();
            Game::GetInstance()->combo = 0;
            std::cout << "\n\nMiss: " << input.GetDeltaRhythm() << "\n\n";
        }
    }

    Game::GetInstance()->GetGridControl()->CheckEnemyAlanCollision(true);
}

void Alan::Update(float dt) {
    if (maxPosition < std::max(associated.gridPosition.y + 4, 7.0)) {
        maxPosition = std::max(associated.gridPosition.y + 4, 7.0);
    }

    GetMovement();
}
