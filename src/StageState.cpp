#include "StageState.h"
#include <stdio.h>
#include "Alien.h"
#include "Camera.h"
#include "Collider.h"
#include "Collision.h"
#include "Endstate.h"
#include "Face.h"
#include "Game.h"
#include "PenguinBody.h"
#include "SDL2/SDL.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

StageState::StageState() {}

void StageState::LoadAssets() {
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

void StageState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void StageState::Update(float dt) {
    Camera::Update(dt);
    UpdateArray(dt);

    bool hasAlien = false;
    bool hasPenguin = false;
    for (auto obj : objectArray) {
        if (obj->GetComponent<Alien*>())
            hasAlien = true;
        else if (obj->GetComponent<PenguinBody*>())
            hasPenguin = true;
    }

    if (!hasPenguin || !hasAlien) {
        Game::GetInstance()->playerVictory = hasPenguin;
        popRequested = true;
        Game::GetInstance()->Push(new EndState());
    }
}

void StageState::Render() const { RenderArray(); }
