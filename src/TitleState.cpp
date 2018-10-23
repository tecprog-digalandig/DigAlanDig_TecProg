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
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(
        new Sprite(*gm, "assets/img/HUD e menus/menu principal/Tela_menu.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 0;
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(new ParallaxX(*gm, 2));
    gm->addComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/Espaço Profundo.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 4300;
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(new ParallaxX(*gm));
    gm->addComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_1.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 3500;
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(new ParallaxX(*gm, 2));
    gm->addComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_2.png"));

    gm = new GameObject(Common::Layer::BG);
    gm->box.x = 0;
    gm->box.y = 5000;
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(new ParallaxX(*gm, 3));
    gm->addComponent(new bgCircularX(
        *gm, "assets/img/HUD e menus/menu principal/nuvem_3.png"));

    gm = new GameObject(Common::Layer::HUD);
    Sprite* sprite =new Sprite(*gm, "assets/img/title.png");
    sprite->SetScaleX(0.45);
    gm->box.setCenter(Camera::Center().x / 2, Camera::Center().y - 50);
    gm->world_reference = false;
    objectArray.emplace_back(gm);
    gm->addComponent(sprite);

    gm = new GameObject(Common::Layer::HUD);
    sprite =new Sprite(*gm, "assets/img/pressSpace.png");
    sprite->SetScaleX(0.9);
    gm->box.setCenter(Camera::Center().x, Camera::Center().y + 300);
    gm->world_reference = false;
    gm->blink = true;
    objectArray.emplace_back(gm);
    gm->addComponent(sprite);

    gm = new GameObject(Common::Layer::HUD);
    sprite =new Sprite(*gm, "assets/img/marmozord_fly.png", 2, -1);
    sprite->SetScaleX(1.4);
    gm->box.setCenter(Camera::Center().x + 220, Camera::Center().y);
    gm->setRect(gm->box);
    gm->world_reference = false;
    gm->move = true;
    objectArray.emplace_back(gm);
    gm->addComponent(sprite);

    Game::getInstance()->StartBeatTime();

    music.isOpen("assets/audio/menu.ogg");
}

void TitleState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void TitleState::Update(float delta_time) {
    input.title = true;
    if (input.actionPress(input.ENTER))
        Game::getInstance()->Push(new StageState());
    UpdateArray(delta_time);
}

void TitleState::render() const { RenderArray(); }

void TitleState::rhythmUpdate() {
    if (!musicPlaying) {
        music.play_func();
        musicPlaying = true;
    }
    rhythmUpdateArray();
    input.shouldShow = !input.shouldShow;
}
