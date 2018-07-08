#include "Camera.h"
#include <iostream>
#include "Alan.h"
#include "AlanAnimation.h"
#include "Game.h"
#include "InputManager.h"
#include "TileMap.h"

Vec2 Camera::pos, Camera::shake, Camera::speed(40, 40), Camera::screenSize;
Vec2 Camera::offset;
Camera::Movement Camera::currentMove = Camera::FRIENDLYSCROLL;

GameObject *Camera::focus = nullptr;
int Camera::shakeIntensity = 0;
float Camera::shakeDuration = 0;

void Camera::Follow(GameObject *newFocus) { focus = newFocus; }

void Camera::Unfollow() { focus = nullptr; }

Vec2 Camera::Center() { return pos + screenSize / 2; }

void Camera::RhythmUpdate() {
    if (focus) {
        if (offset.y > (focus->box.y +
                        Game::GetInstance()->GetCurrentState().GetGridSize()) &&
            focus->GetComponent<Alan *>()->GetHP() > 0) {
            focus->GetComponent<Alan *>()->TakeDamage();
        }
    }
}

void Camera::Update(float dt) {
    if (shakeDuration > 0) {
        shakeDuration -= dt;
        shake = {sin((rand() % (int)(2000 * M_PI)) / 1000.0) * shakeIntensity,
                 sin((rand() % (int)(2000 * M_PI)) / 1000.0) * shakeIntensity};
    } else {
        shake = {0, 0};
    }

    if (!focus) currentMove = Camera::NONE;

    float scrollFactor = 1;

    switch (Camera::currentMove) {
        case ATTACHED:
            if (focus->box.y >= screenSize.y / 2) {
                offset.y = -(screenSize.y / 2) + focus->box.y;
            }
            break;

        case Camera::FRIENDLYSCROLL:
            // half the speed when close to the top
            // double the speed when close to the bottom
            scrollFactor = (1.5 * (focus->box.y - pos.y) / screenSize.y + 0.5);

        case Camera::CONSTSCROLL: {
            Vec2 focusGridPos = focus->GetGridPosition();
            TileMap *tileMap = Game::GetInstance()->GetCurrentState().tileMap;

            if (focus->GetComponent<AlanAnimation *>()->GetCurrentState() ==
                AlanAnimation::State::DEAD) {
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
                offset.y += speed.y * dt * scrollFactor;

                if (offset.y + screenSize.y - 300 < focus->box.y) {
                    offset.y += 3 * speed.y * dt * scrollFactor;
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

    static int acc = 30;
    if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_COMMA)) {
        speed.y -= acc * dt;
    }
    if (InputManager::GetInstance().KeyDown(SDL_SCANCODE_PERIOD)) {
        speed.y += acc * dt;
    }
    if (InputManager::GetInstance().KeyPress(SDL_SCANCODE_C)) {
        currentMove = (Movement)(currentMove + 1);
        if (currentMove > Camera::NONE) currentMove = Camera::ATTACHED;
    }
}

void Camera::Shake(int intensity, float duration) {
    shakeIntensity = intensity;
    shakeDuration = duration;
}
