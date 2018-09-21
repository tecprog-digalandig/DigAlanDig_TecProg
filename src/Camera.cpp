#include "Camera.h"
#include <iostream>
#include "Alan.h"
#include "AlanAnimation.h"
#include "Game.h"
#include "InputManager.h"
#include "TileMap.h"

Vec2 Camera::pos, Camera::shake, Camera::speed(60, 60), Camera::screenSize;
Vec2 Camera::offset;
Camera::Movement Camera::current_move = Camera::FRIENDLYSCROLL;

GameObject *Camera::focus = nullptr;
int Camera::shake_intensity = 0;
float Camera::shake_duration = 0;

void Camera::Follow(GameObject *new_focus) 
{ 
    focus = new_focus;
}

void Camera::Unfollow()
{ 
    focus = nullptr;
}

Vec2 Camera::Center()
{ 
    return pos + screenSize / 2;
}

void Camera::rhythmUpdate()
{
    if (focus) {
        if (offset.y > (focus->box.y +
                        Game::GetInstance()->GetCurrentState().GetGridSize()) &&
            focus->GetComponent<Alan *>()->GetHP() > 0) {
            focus->GetComponent<Alan *>()->TakeDamage();
        }
    }
}

void Camera::update(float dt)
{
    if (shake_duration > 0) {
        shake_duration -= dt;
        shake = {sin((rand() % (int)(2000 * M_PI)) / 1000.0) * shake_intensity,
                 sin((rand() % (int)(2000 * M_PI)) / 1000.0) * shake_intensity};
    } else {
        shake = {0, 0};
    }

    if (!focus) current_move = Camera::NONE;

    float scroll_factor = 1;

    switch (Camera::current_move) {
        case ATTACHED:
            if (focus->box.y >= screenSize.y / 2) {
                offset.y = -(screenSize.y / 2) + focus->box.y;
            }
            break;

        case Camera::FRIENDLYSCROLL:
            // half the speed when close to the top
            // double the speed when close to the bottom
            scroll_factor = (1.5 * (focus->box.y - pos.y) / screenSize.y + 0.5);

        case Camera::CONSTSCROLL: {
            Vec2 focusGridPos = focus->GetGridPosition();
            TileMap *tileMap = Game::GetInstance()->GetCurrentState().tileMap;

            if (focus->GetComponent<AlanAnimation *>()->GetCurrentState() ==
                    AlanAnimation::State::DEAD ||
                focus->GetComponent<AlanAnimation *>()->GetCurrentState() ==
                    AlanAnimation::State::DANCIN) {
                if (offset.y >
                        ((focusGridPos.y + 1) * 100 - screenSize.y / 2) &&
                    offset.y > 0) {
                    offset.y -= dt * 400;
                }
                break;
            }

            if (focusGridPos.y != 0 &&
                offset.y <=
                    (tileMap->GetHeight() *
                         Game::GetInstance()->GetCurrentState().GetGridSize() -
                     screenSize.y)) {
                offset.y += speed.y * dt * scroll_factor;

                if (offset.y + screenSize.y - 300 < focus->box.y) {
                    offset.y += 3 * speed.y * dt * scroll_factor;
                }
            }
            break;
        }

        case Camera::NONE:
            if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_UP)) {
                offset.y -= speed.y * dt * 10;
            }
            if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_DOWN)) {
                offset.y += speed.y * dt * 10;
            }
            break;
    }
    pos = shake + offset;

    static int acceleration = 30;
    if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_COMMA)) {
        speed.y -= acceleration * dt;
    }
    if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_PERIOD)) {
        speed.y += acceleration * dt;
    }
    if (InputManager::GetInstance().KeyPress(SDL_SCANCODE_C)) {
        current_move = (Movement)(current_move + 1);
        if (current_move > Camera::NONE) current_move = Camera::ATTACHED;
    }
}

void Camera::Shake(int intensity, float duration)
{
    shake_intensity = intensity;
    shake_duration = duration;
}
