/**
 * @brief 
 * 
 * @file BigAlan.cpp
 * @brief refresh character animation
 */
#include "BigAlan.h"
#include "Game.h"
#include "AlanAnimation.h"
#include "InputManager.h"
#include "GridControl.h"

/**
 * @brief will perform the animation depending on the current status of bigAlan
 * 
 * @param dt 
 */
void BigAlan::Update(float dt) 
{
    // calculations of the combos that will be used 
    // to define the bigAlan animation
    int combo = Game::GetInstance()->combo;
    int diff_combo = std::abs(combo - old_combo);
    old_combo = combo;
    // You need to check if the character is already dead 
    // to put the "TRASH" animation in the current state
    if(Game::GetInstance()->GetGridControl()->GetAlan().lock()->GetComponent<AlanAnimation *>()->GetCurrentState() == AlanAnimation::State::DEAD){
        // the "TRASH" image is assigned to the current status
        if(current_state != BAState::TRASH){
            current_state = BAState::TRASH;
            sprite->Open(state[current_state], 0);
        } // if -- animation dead
        return;
    } // if -- end of verification
    BAState old_state = current_state;
    // the character will receive the image of the current 
    // state according to the combo that was calculated
    switch (current_state) {
        case BAState::STARTER:
        case BAState::GOOD:
            // checks the character combo to assign 
            // the image to the current state
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