#include "Camera.h"
#include <iostream>
#include "InputManager.h"

Vec2 Camera::pos, Camera::speed(200, 200), Camera::screenSize;
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) { focus = newFocus; }

void Camera::Unfollow() { focus = nullptr; }

Vec2 Camera::Center() { return pos + screenSize / 2; }

void Camera::Update(float dt) {
    if (focus) {
        // pos = focus->box.Center() - screenSize / 2;
        if (focus->box.y >= screenSize.y / 2) {
            pos.y = -(screenSize.y / 2) + focus->box.y;
        }
        return;
    }
    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_RIGHT)) {
        pos.x += speed.x * dt;
    }
    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        pos.x -= speed.x * dt;
    }
    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_UP)) {
        pos.y -= speed.y * dt;
    }
    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_DOWN)) {
        pos.y += speed.y * dt;
    }

    // std::cout << "Pos: " << pos << std::endl << "Speed: " << speed <<
    // std::endl;
}
