#define INCLUDE_SDL
#include <stdio.h>
#include "TitleState.h"
#include "SDL_include.h"
#include "Camera.h"
#include "Game.h"
#include "Parallax.h"
#include "Sound.h"
#include "Sprite.h"
#include "StageState.h"
#include "TileMap.h"
#include "Vec2.h"
#define POSITION_X_SPACE 0
#define POSITION_Y_SPACE 0
#define SPACE_VELOCITY 2
#define POSITION_X_CLOUD 0
#define POSITION_Y_CLOUD 4300
#define POSITION_X_CLOUD_2 0
#define POSITION_Y_CLOUD_2 3500
#define CLOUD_2_VELOCITY 2
#define POSITION_X_CLOUD_3 0
#define POSITION_Y_CLOUD_3 5000
#define CLOUD_3_VELOCITY 3
#define MENU_SCREEN "assets/img/HUD_e_menus/menu_principal/Tela_menu.png"
#define SPACE_SCREEN "assets/img/HUD_e_menus/menu_principal/Espaço_Profundo.png"
#define CLOUD_1 "assets/img/HUD_e_menus/menu_principal/nuvem_1.png"
#define CLOUD_2 "assets/img/HUD_e_menus/menu_principal/nuvem_2.png"
#define CLOUD_3 "assets/img/HUD_e_menus/menu_principal/nuvem_3.png"
#define TITLE_MENU "assets/img/title.png"
#define TITLE_PRESS_SPACE "assets/img/pressSpace.png"
#define SPACESHIP_MENU "assets/img/marmozord_fly.png"
#define AUDIO_MENU "assets/audio/menu.ogg"
#define SCALE_X_TITLE 0.45
#define POSITION_X_TITLE Camera::Center().x / 2
#define POSITION_Y_TITLE Camera::Center().y - 50
#define SCALE_X_PRESS_SPACE 0.9
#define POSITION_X_PRESS_SPACE Camera::Center().x
#define POSITION_Y_PRESS_SPACE Camera::Center().y + 300
#define SCALE_X_SPACESHIP 1.4
#define POSITION_X_SPACESHIP Camera::Center().x + 200
#define POSITION_Y_SPACESHIP Camera::Center().y


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


void TitleState::Start()
{
    if (!started) loadAssets();
    StartArray();
}

void TitleState::Update(float delta_time) {
    input.title = true;
    if (input.actionPress(input.ENTER))
        Game::getInstance()->Push(new stageState());
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
