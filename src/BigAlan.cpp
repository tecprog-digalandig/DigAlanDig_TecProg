#include "BigAlan.h"
#include "Game.h"
#include "AlanAnimation.h"
#include "InputManager.h"
#include "GridControl.h"


void BigAlan::Update(float dt) 
{
    int combo = Game::GetInstance()->combo;
    int diff_combo = std::abs(combo - old_combo);
    old_combo = combo;
    if(Game::GetInstance()->GetGridControl()->GetAlan().lock()->GetComponent<AlanAnimation *>()->GetCurrentState() == AlanAnimation::State::DEAD){
        if(current_state != BAState::TRASH){
            current_state = BAState::TRASH;
            sprite->Open(state[current_state], 0);
        }
        return;
    }
    BAState old_state = current_state;
    switch (current_state) {
        case BAState::STARTER:
        case BAState::GOOD:
            if (Game::GetInstance()->combo > 10)
                current_state = BAState::GOOD;
            else if (diff_combo > 5)
                current_state = BAState::DECENT;
            else if (diff_combo > 10)
                current_state = BAState::TRASH;
            break;
        case BAState::DECENT:
            if (Game::GetInstance()->combo > 2) current_state = BAState::STARTER;
            break;
        case BAState::TRASH:
            if (Game::GetInstance()->combo > 3) current_state = BAState::STARTER;
            break;
        default:
            current_state = BAState::STARTER;
    }
    if (current_state != old_state) sprite->Open(state[current_state], 0);
}
