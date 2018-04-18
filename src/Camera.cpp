#include "Camera.h"
#include <iostream>
#include "InputManager.h"

Vec2 Camera::pos, Camera::speed(200, 200);
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) { focus = newFocus; }

void Camera::Unfollow() { focus = nullptr; }

void Camera::Update(float dt) {
    if (focus) {
        pos = focus->box.pos;
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

    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_EQUALS)) {
        speed += dt * 50;
    }
    if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_MINUS)) {
        speed -= dt * 50;
    }

    std::cout << "Pos: " << pos << std::endl << "Speed: " << speed << std::endl;
}
