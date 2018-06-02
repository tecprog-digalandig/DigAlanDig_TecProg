#include "State.h"
#include <stdio.h>
#include "Camera.h"
#include "Collider.h"
#include "Collision.h"
#include "SDL2/SDL.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

State::State() : input(InputManager::GetInstance()) {}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.emplace_back(ptr);
    if (started) ptr->Start();

    // std::weak_ptr a = prt;
    return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPrt(GameObject* go) {
    std::weak_ptr<GameObject> wp;
    for (std::shared_ptr<GameObject>& obj : objectArray) {
        if (obj.get() == go) {
            wp = obj;
            break;
        }
    }

    return wp;
}

void State::StartArray() {
    if (started) return;

    //    for (auto obj : objectArray) obj->Start();
    for (size_t i = 0; i < objectArray.size(); i++) objectArray[i]->Start();

    started = true;
}

void State::UpdateArray(float dt) {
    // Update
    //    for (auto obj : objectArray) obj->Update(dt);
    for (size_t i = 0; i < objectArray.size(); i++) objectArray[i]->Update(dt);

    // Delete
    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    // KeyPress
    if (input.KeyPress(SDL_SCANCODE_ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::RhythmUpdateArray() {
    for (auto obj : objectArray) obj->RhythmUpdate();
}

void State::RhythmResetArray() {
    for (auto obj : objectArray) obj->RhythmReset();
}

void State::RenderArray() const {
    for (auto obj : objectArray) obj->Render();
}
