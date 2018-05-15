#include "State.h"
#include <stdio.h>
#include "Alien.h"
#include "Camera.h"
#include "Collider.h"
#include "Collision.h"
#include "Face.h"
#include "PenguinBody.h"
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

    // for (auto& obj : objectArray) obj->Start();
    for (int i = 0; i < (int)objectArray.size(); i++) objectArray[i]->Start();

    started = true;
}

void State::UpdateArray(float dt) {
    // Update
    for (int i = 0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // Delete
    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    // Collision
    for (int i = 0; i < (int)objectArray.size(); i++) {
        auto ci = objectArray[i]->GetComponent<Collider*>();
        if (!ci) continue;

        for (int j = i + 1; j < (int)objectArray.size(); j++) {
            auto cj = objectArray[j]->GetComponent<Collider*>();
            if (!cj) continue;

            if ((objectArray[i]->fromPlayer != objectArray[j]->fromPlayer) &&
                Collision::IsColliding(ci->box, cj->box,
                                       objectArray[i]->AngleRad(),
                                       objectArray[j]->AngleRad())) {
                objectArray[i]->NotifyCollision(objectArray[j]);
                objectArray[j]->NotifyCollision(objectArray[i]);
                std::cout << std::endl;
            }
        }
    }

    // KeyPress
    if (input.KeyPress(SDL_SCANCODE_ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::RenderArray() const {
    for (auto& obj : objectArray) obj->Render();
}
