#include "AlanActionControl.h"
#include "Alan.h"
#include "AlanItemCount.h"
#include "Game.h"
#include "Interpol.h"
#include "Sprite.h"

bool AlanActionControl::ShouldFall() {
    return gridsLeft ||
           ((Game::GetInstance()->GetGridControl()->TestPath(
                 Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::FREE ||
             Game::GetInstance()->GetGridControl()->TestPath(
                 Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                 true) == GridControl::WhatsThere::ENEMY));
}

void AlanActionControl::Fallin(float dt) {
    if (gridsLeft > 0) gridsLeft--;
    associated.gridPosition.y++;
    associated.GetComponent<Sprite *>()->TimeElapsedReset();
}

bool AlanActionControl::IsFree() {
    if (movementDirection == Direction::LEFT &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) {
        return true;
    }

    if (movementDirection == Direction::RIGHT &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::FREE) {
        return true;
    }

    return false;
}

bool AlanActionControl::IsBlock() {
    if (movementDirection == Direction::LEFT &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x - 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) {
        return true;
    }

    if (movementDirection == Direction::RIGHT &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x + 1, associated.gridPosition.y),
            true) == GridControl::WhatsThere::ROCK) {
        return true;
    }
    return false;
}

bool AlanActionControl::CanClimb() {
    return input.KeyDown(SDL_SCANCODE_A) && action != Action::WALKIN;
}

bool AlanActionControl::InClimbPosition(AlanAnimation *animation) {
    return (animation->GetCurrentState() == AlanAnimation::State::CLIMBIN ||
            animation->GetOldState() == AlanAnimation::State::CLIMBIN) &&
           animation->GetCurrentState() != AlanAnimation::State::IDLE;
}

bool AlanActionControl::ClimbPathFree() {
    if (movementDirection == Direction::UP &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
            true) == GridControl::WhatsThere::FREE) {
        return true;
    }

    if (movementDirection == Direction::DOWN &&
        Game::GetInstance()->GetGridControl()->TestPath(
            Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
            true) == GridControl::WhatsThere::FREE) {
        return true;
    }

    return false;
}

bool AlanActionControl::IsClimbDirectionLeft(AlanAnimation *animation) {
    return (animation->GetCurrentDirection() ==
                AlanAnimation::Direction::LEFT ||
            animation->GetOldDirection() == AlanAnimation::Direction::LEFT) &&
           animation->GetCurrentDirection() != AlanAnimation::Direction::RIGHT;
}

void AlanActionControl::Update(float dt) {
    if (!associated.GetComponent<Interpol *>()->IsMovementDone()) return;

    Alan *alan = associated.GetComponent<Alan *>();
    AlanAnimation *animation = associated.GetComponent<AlanAnimation *>();
    TileMap *tileMap = Game::GetInstance()->GetCurrentState().tileMap;
    Sprite *sprite = associated.GetComponent<Sprite *>();

    if (alan->GetItemCount()
            ->GetComponent<AlanItemCount *>()
            ->CollectedAllItens()) {
        if (animation->GetCurrentState() != AlanAnimation::State::DANCIN) {
            animation->SetAction(AlanAnimation::Transition::DANCE,
                                 AlanAnimation::Direction::LEFT);
        }

        return;
    }

    if (alan->GetHP() <= 0) {
        if (animation->GetCurrentState() != AlanAnimation::State::DEAD) {
            animation->SetAction(AlanAnimation::Transition::DIE,
                                 AlanAnimation::Direction::LEFT);
        }

        if (sprite->FrameTimePassed()) {
            Game::GetInstance()->combo = 0;
        }
        return;
    }

    // Testa se a marmota deve "cair" ou ficar na posição atual
    if (ShouldFall()) {
        if (gridsLeft == 0) {
            movementDirection = Direction::DOWN;
            action = Action::FALLIN;
            int y = associated.gridPosition.y + 1;
            while (!tileMap->At(associated.gridPosition.x, y)) {
                gridsLeft++;
                y++;
            }
            animation->SetAction(AlanAnimation::Transition::FALL,
                                 AlanAnimation::Direction::LEFT);
        }

        Fallin(dt);

        return;
    }

    if (animation->GetCurrentState() == AlanAnimation::State::FALLIN) {
        animation->SetAction(AlanAnimation::Transition::FLOOR,
                             AlanAnimation::Direction::LEFT);
        action = Action::STANDIN;
        movementDirection = Direction::NONE;
    }

    if (movementDirection == Direction::NONE) {
        if (action != Action::CLIMBING || !input.KeyDown(SDL_SCANCODE_A)) {
            animation->SetAction(AlanAnimation::Transition::NONE_T,
                                 AlanAnimation::Direction::LEFT);
            action = Action::STANDIN;
        }

        return;
    }

    if (action != Action::WALKIN) {
        action = Action::WALKIN;
    }
    // Up bate na pedra acima dele se houver
    if (movementDirection == Direction::UP) {
        if (Game::GetInstance()->GetGridControl()->TestPath(
                Vec2(associated.gridPosition.x, associated.gridPosition.y - 1),
                true) == GridControl::WhatsThere::ROCK) {
            if (int itemType = Game::GetInstance()->GetGridControl()->IsItem(
                    Vec2(associated.gridPosition.x,
                         associated.gridPosition.y - 1))) {
                tileMap->ItemCollected(Vec2(associated.gridPosition.x,
                                            associated.gridPosition.y - 1),
                                       TileMap::Layers::ITENS);
                alan->GetItemCount()
                    ->GetComponent<AlanItemCount *>()
                    ->ItemCollected(itemType);
            }

            if (!animationOnGoing) {
                animation->SetAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::UP);
                animationOnGoing = true;
            }
            if (sprite->FrameTimePassed()) {
                tileMap->GetDamageGround(alan->GetDamage(),
                                         Vec2(associated.gridPosition.x,
                                              associated.gridPosition.y - 1));
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

            return;
        } else {
            movementDirection = Direction::NONE;
        }
        // Down bate na pedra embaixo dele
    } else if (movementDirection == Direction::DOWN) {
        if (int itemType = Game::GetInstance()->GetGridControl()->IsItem(Vec2(
                associated.gridPosition.x, associated.gridPosition.y + 1))) {
            tileMap->ItemCollected(
                Vec2(associated.gridPosition.x, associated.gridPosition.y + 1),
                TileMap::Layers::ITENS);
            alan->GetItemCount()
                ->GetComponent<AlanItemCount *>()
                ->ItemCollected(itemType);

            animation->SetAction(AlanAnimation::Transition::DIG_T,
                                 AlanAnimation::Direction::DOWN);

            tileMap->GetDamageGround(
                alan->GetDamage(),
                Vec2(associated.gridPosition.x, associated.gridPosition.y + 1));
            movementDirection = Direction::NONE;
            associated.gridPosition.y++;
        } else {
            if (!animationOnGoing) {
                animation->SetAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::DOWN);
                animationOnGoing = true;
            }
            if (sprite->FrameTimePassed()) {
                tileMap->GetDamageGround(alan->GetDamage(),
                                         Vec2(associated.gridPosition.x,
                                              associated.gridPosition.y + 1));
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }
        }
    } else if (movementDirection == Direction::LEFT) {
        // Testa se o valor do grid a esquerda é uma
        // pedra
        if (!IsFree()) {
            if (int itemType = Game::GetInstance()->GetGridControl()->IsItem(
                    Vec2(associated.gridPosition.x - 1,
                         associated.gridPosition.y))) {
                tileMap->ItemCollected(Vec2(associated.gridPosition.x - 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->GetItemCount()
                    ->GetComponent<AlanItemCount *>()
                    ->ItemCollected(itemType);
            }

            if (!animationOnGoing) {
                animation->SetAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::LEFT);
                animationOnGoing = true;
            }
            if (sprite->FrameTimePassed()) {
                if (IsBlock()) {
                    tileMap->GetDamageGround(alan->GetDamage(),
                                             Vec2(associated.gridPosition.x - 1,
                                                  associated.gridPosition.y));
                }
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

        } else {
            animation->SetAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::LEFT);

            movementDirection = Direction::NONE;
            associated.gridPosition.x--;
        }
    } else {
        // Mesmo processo anterior para a direita
        if (!IsFree()) {
            if (int itemType = Game::GetInstance()->GetGridControl()->IsItem(
                    Vec2(associated.gridPosition.x + 1,
                         associated.gridPosition.y))) {
                tileMap->ItemCollected(Vec2(associated.gridPosition.x + 1,
                                            associated.gridPosition.y),
                                       TileMap::Layers::ITENS);
                alan->GetItemCount()
                    ->GetComponent<AlanItemCount *>()
                    ->ItemCollected(itemType);
            }

            if (!animationOnGoing) {
                animation->SetAction(AlanAnimation::Transition::DIG_T,
                                     AlanAnimation::Direction::RIGHT);
                animationOnGoing = true;
            }
            if (sprite->FrameTimePassed()) {
                if (IsBlock()) {
                    tileMap->GetDamageGround(alan->GetDamage(),
                                             Vec2(associated.gridPosition.x + 1,
                                                  associated.gridPosition.y));
                }
                movementDirection = Direction::NONE;
                animationOnGoing = false;
            }

        } else {
            animation->SetAction(AlanAnimation::Transition::WALK,
                                 AlanAnimation::Direction::RIGHT);

            movementDirection = Direction::NONE;
            associated.gridPosition.x++;
            animationOnGoing = false;
        }
    }
    if (animation->GetCurrentState() == AlanAnimation::State::IDLE) {
        animationOnGoing = false;
    }
}
