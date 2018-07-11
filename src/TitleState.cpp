#include "TitleState.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>
#include "Camera.h"
#include "Game.h"
#include "Parallax.h"
#include "Sound.h"
#include "Sprite.h"
#include "StageState.h"
#include "TileMap.h"
#include "Vec2.h"

TitleState::TitleState() {}

void TitleState::LoadAssets() {
    GameObject* gm = new GameObject(Common::Layer::BG);
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(
        new Sprite(*gm, "assets/img/HUD e menus/menu principal/Tela_menu.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 0;
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new ParallaxX(*gm, 2));
    gm->AddComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/Espaço Profundo.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 4300;
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new ParallaxX(*gm));
    gm->AddComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_1.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 3500;
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new ParallaxX(*gm, 2));
    gm->AddComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_2.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 5000;
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new ParallaxX(*gm, 3));
    gm->AddComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_3.png"));

    gm = new GameObject(Common::Layer::HUD);
    Sprite* sprite = new Sprite(*gm, "assets/img/title.png");
    sprite->SetScaleX(0.45);
    gm->box.SetCenter(Camera::Center().x / 2, Camera::Center().y - 50);
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(sprite);

    gm = new GameObject(Common::Layer::HUD);
    sprite = new Sprite(*gm, "assets/img/pressSpace.png");
    sprite->SetScaleX(0.9);
    gm->box.SetCenter(Camera::Center().x, Camera::Center().y + 300);
    gm->worldReference = false;
    gm->blink = true;
    objectArray.emplace_back(gm);
    gm->AddComponent(sprite);

    gm = new GameObject(Common::Layer::HUD);
    sprite = new Sprite(*gm, "assets/icon/Icon_funk.png");
    sprite->SetScaleX(1);
    gm->box.SetCenter(Camera::Center().x + 220, Camera::Center().y);
    gm->setRect(gm->box);
    gm->worldReference = false;
    gm->move = true;
    objectArray.emplace_back(gm);
    gm->AddComponent(sprite);

    Game::GetInstance()->StartBeatTime();

    music.Open("assets/audio/menu.ogg");
}

void TitleState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void TitleState::Update(float dt) {
    input.title = true;
    if (input.ActionPress(input.ENTER))
        Game::GetInstance()->Push(new StageState());
    UpdateArray(dt);
}

void TitleState::Render() const { RenderArray(); }

void TitleState::RhythmUpdate() {
    if (!musicPlaying) {
        music.Play();
        musicPlaying = true;
    }
    RhythmUpdateArray();
    input.shouldShow = !input.shouldShow;
}
