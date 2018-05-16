#include "TitleState.h"
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
#include "StageState.h"
#include "Text.h"
#include "TileMap.h"
#include "Vec2.h"

TitleState::TitleState() {}

void TitleState::LoadAssets() {
    GameObject* gm = new GameObject();
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/title.jpg"));

    gm = new GameObject();
    gm->box.SetCenter(Camera::Center());
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new Text(*gm, "assets/font/Call me maybe.ttf", 72,
                              Text::TextStyle::BLENDED, "Press Space to begin",
                              {0, 0, 0, 255}, 1));
}

void TitleState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void TitleState::Update(float dt) {
    if (input.KeyPress(SDL_SCANCODE_SPACE))
        Game::GetInstance()->Push(new StageState());
    UpdateArray(dt);
}

void TitleState::Render() const { RenderArray(); }
