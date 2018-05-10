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

State::State(void) : input(InputManager::GetInstance()) {}

void State::LoadAssets() {
    GameObject* gm = new GameObject();
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/ocean.jpg"));
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    gm->AddComponent(new TileMap(*gm, "assets/map/tileMap.txt", tileSet));

    GameObject* gm2 = new GameObject();
    gm2->box.SetCenter(512, 300);
    objectArray.emplace_back(gm2);
    gm2->AddComponent(new Alien(*gm2, 6));

    GameObject* gm3 = new GameObject();
    gm3->box.pos.Set(704, 640);
    objectArray.emplace_back(gm3);
    gm3->AddComponent(new PenguinBody(*gm3));

    Camera::Follow(gm3);

    music = new Music("assets/audio/stageState.ogg");
    music->Play(2);
}

void State::Start() {
    if (started) return;

    LoadAssets();
    // for (auto& obj : objectArray) obj->Start();
    for (int i = 0; i < (int)objectArray.size(); i++) objectArray[i]->Start();

    started = true;
}

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

void State::Update(float dt) {
    // Update
    for (int i = 0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    Camera::Update(dt);

    // Delete
    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    // Collision
    for (int i = 0; i < (int)objectArray.size(); i++) {
        Collider* ci = (Collider*)objectArray[i]->GetComponent("Collider");
        if (!ci) continue;

        for (int j = i + 1; j < (int)objectArray.size(); j++) {
            Collider* cj = (Collider*)objectArray[j]->GetComponent("Collider");
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

void State::Render() const {
    for (auto& obj : objectArray) obj->Render();
}

void State::AddObject(int mouseX, int mouseY) {}
