#include "BigAlan.h"
#include "Game.h"
#include "AlanAnimation.h"
#include "InputManager.h"
#include "GridControl.h"


void BigAlan::Update(float delta_time) {
    int combo = Game::getInstance()->combo;
    int diffCombo = std::abs(combo - oldCombo);
    oldCombo = combo;

    if(Game::getInstance()->getGridControl()->GetAlan().lock()->GetComponent<AlanAnimation *>()->getCurrentState() == AlanAnimation::State::dead){
        if(currentState != BAState::TRASH){
            currentState = BAState::TRASH;
            sprite->Open(state[currentState], 0);
        }
        return;
    }
    
    BAState oldState = currentState;
    switch (currentState) {
        case BAState::STARTER:
        case BAState::GOOD:
            if (Game::getInstance()->combo > 10)
                currentState = BAState::GOOD;
            else if (diffCombo > 5)
                currentState = BAState::DECENT;
            else if (diffCombo > 10)
                currentState = BAState::TRASH;

            break;

        case BAState::DECENT:
            if (Game::getInstance()->combo > 2) currentState = BAState::STARTER;
            break;

        case BAState::TRASH:
            if (Game::getInstance()->combo > 3) currentState = BAState::STARTER;
            break;

        default:
            currentState = BAState::STARTER;
    }

    if (currentState != oldState) sprite->Open(state[currentState], 0);
}
