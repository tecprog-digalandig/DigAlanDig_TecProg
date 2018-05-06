#include "State.h"
#include <stdio.h>
#include "Alien.h"
#include "Camera.h"
#include "Face.h"
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
    objectArray.emplace_back(gm2);
    gm2->AddComponent(new Alien(*gm2, 6));
    gm2->box.SetCenter(512, 300);

    music = new Music("assets/audio/stageState.ogg");
    music->Play(2);
}

void State::Start() {
    if (started) return;

    LoadAssets();
    for (auto& obj : objectArray) obj->Start();

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
        std::cout << "Get " << go << " got " << obj;
        if (obj.get() == go) {
            wp = obj;
            break;
        }
    }

    return wp;
}

void State::Update(float dt) {
    for (auto& obj : objectArray) obj->Update(dt);
    Camera::Update(dt);

    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    if (input.KeyPress(SDL_SCANCODE_SPACE)) {
        Vec2 objPos = Vec2(200, 0).Rotate(rand() % 361) +
                      Vec2(input.GetWorldMouseX(), input.GetWorldMouseY());
        AddObject((int)objPos.x, (int)objPos.y);
    }
    if (input.KeyPress(SDL_SCANCODE_ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::Render() const {
    for (auto& obj : objectArray) obj->Render();
}

void State::AddObject(int mouseX, int mouseY) {}
