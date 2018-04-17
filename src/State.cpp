#include "State.h"
#include <stdio.h>
#include "Face.h"
#include "SDL2/SDL.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

State::State(void) : quitRequested(false), input(InputManager::GetInstance()) {
    GameObject* gm = new GameObject();
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/ocean.jpg"));
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    gm->AddComponent(new TileMap(*gm, "assets/map/tileMap.txt", tileSet));

    music = new Music("assets/audio/stageState.ogg");
    music->Play(2);
}

void State::Update(float dt) {
    for (auto& obj : objectArray) obj->Update(dt);

    auto removeDead = [&](std::unique_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    if (input.KeyPress(SDL_SCANCODE_SPACE)) {
        Vec2 objPos = Vec2(200, 0).rotate(rand() % 361) +
                      Vec2(input.GetMouseX(), input.GetMouseY());
        AddObject((int)objPos.x, (int)objPos.y);
    }
    if (input.KeyPress(SDL_SCANCODE_ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::Render() const {
    for (auto& obj : objectArray) obj->Render();
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* gm = new GameObject();
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/penguinface.png"));
    gm->AddComponent(new Sound(*gm, "assets/audio/boom.wav"));
    gm->AddComponent(new Face(*gm));

    std::cout << "New Object" << std::endl;
    gm->box.pos.set(mouseX - gm->box.w / 2, mouseY - gm->box.h / 2);
}
