/*
* File: TitleState.cpp
* Purpose: Create the initial layout to show the game title
*/
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
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //
#include "spdlog/sinks/basic_file_sink.h" // 
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
#define SCALE_X_SPACESHIP 1.4
#define POSITION_Y_PRESS_SPACE Camera::Center().y + 300
#define POSITION_X_SPACESHIP Camera::Center().x + 200
#define POSITION_Y_SPACESHIP Camera::Center().y
    

TitleState::TitleState() {}

void TitleState::loadAssets() 
{   
        
    auto my_logger = spdlog::basic_logger_mt("log", "logs/basic.txt"); 
    auto console = spdlog::stdout_color_mt("console");  
    
    GameObject* initial_layout = new GameObject(Common::Layer::BG);  
    addBackgroud(initial_layout);
     
    // Add the first moving cloud to the layout
    initial_layout = new GameObject(Common::Layer::BG);
    initial_layout->box.x = POSITION_X_CLOUD;   
    initial_layout->box.y = POSITION_Y_CLOUD;   
    initial_layout->world_reference = false;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(new ParallaxX(*initial_layout));
    initial_layout->AddComponent(new bgCircularX(
        *initial_layout, CLOUD_1)); 
    //my_logger->info("First moving cloud has been added to the menu");

    // Add the second moving cloud to the layout
    initial_layout = new GameObject(Common::Layer::BG);
    initial_layout->box.x = POSITION_X_CLOUD_2; 
    initial_layout->box.y = POSITION_Y_CLOUD_2; 
    initial_layout->world_reference = false;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(new ParallaxX(*initial_layout, CLOUD_2_VELOCITY)); 
    initial_layout->AddComponent(new bgCircularX(*initial_layout, CLOUD_2));    
    //my_logger->info("Second moving cloud has been added to the menu");

    // Add the third moving cloud to the layout
    initial_layout = new GameObject(Common::Layer::BG);
    initial_layout->box.x = POSITION_X_CLOUD_3; 
    initial_layout->box.y = POSITION_Y_CLOUD_3; 
    initial_layout->world_reference = false;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(new ParallaxX(*initial_layout, CLOUD_3_VELOCITY)); 
    initial_layout->AddComponent(new bgCircularX(*initial_layout, CLOUD_3));      
    //my_logger->info("Third moving cloud has been added to the menu"); 

    // Add title to the layout
    initial_layout = new GameObject(Common::Layer::HUD);
    Sprite* sprite = new Sprite(*initial_layout, TITLE_MENU);   
    sprite->SetScaleX(SCALE_X_TITLE);   
    initial_layout->box.SetCenter(POSITION_X_TITLE, POSITION_Y_TITLE);  
    initial_layout->world_reference = false;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(sprite);
    //my_logger->info("Title has been added to the menu");  

    // add image "Press Space" to the layout
    initial_layout = new GameObject(Common::Layer::HUD);
    sprite = new Sprite(*initial_layout, TITLE_PRESS_SPACE);    
    sprite->SetScaleX(SCALE_X_PRESS_SPACE); 
    initial_layout->box.SetCenter(POSITION_X_PRESS_SPACE, POSITION_Y_PRESS_SPACE);  
    initial_layout->world_reference = false;
    initial_layout->blink = true;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(sprite);
    //my_logger->info("Press Space has been added to the menu");

    // add spaceship to the layout
    initial_layout = new GameObject(Common::Layer::HUD);
    sprite = new Sprite(*initial_layout, SPACESHIP_MENU, 2, -1);    
    sprite->SetScaleX(SCALE_X_SPACESHIP);   
    initial_layout->box.SetCenter(POSITION_X_SPACESHIP, POSITION_Y_SPACESHIP);  
    initial_layout->setRect(initial_layout->box);
    initial_layout->world_reference = false;
    initial_layout->move = true;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(sprite);
    //my_logger->info("Spaceship has been added to the menu");

    Game::GetInstance()->StartBeatTime();
    music.Open(AUDIO_MENU); 

}

// Add background to layout    
void TitleState::addBackgroud(GameObject* initial_layout){
    initial_layout->world_reference = false;    
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(
    new Sprite(*initial_layout, MENU_SCREEN));  
    //my_logger->info("Background has been added to the menu");  
}

// Add moving space to layout
void TitleState::addMovingSpace(GameObject* initial_layout){
    initial_layout = new GameObject(Common::Layer::BG);
    initial_layout->box.x = POSITION_X_SPACE;      
    initial_layout->box.y = POSITION_Y_SPACE;      
    initial_layout->world_reference = false;
    objectArray.emplace_back(initial_layout);
    initial_layout->AddComponent(new ParallaxX(*initial_layout, SPACE_VELOCITY));   
    initial_layout->AddComponent(new bgCircularX(
        *initial_layout, SPACE_SCREEN));
    //my_logger->info("Moving space has been added to the menu");

}

void TitleState::start() {
    if (!started){
        loadAssets();
    } 
    else{ 
        // There's nothing to do
    }

    StartArray();
}

void TitleState::update(float delta_time)  {
    input.title = true;
    if (input.ActionPress(input.ENTER)){
        Game::GetInstance()->Push(new StageState());
    }
    else{ 
        // There's nothing to do
    }

    UpdateArray(delta_time);
}

void TitleState::render() const { RenderArray(); }

void TitleState::rhythmUpdate() {
    if (!musicPlaying) {
        music.Play();
        musicPlaying = true;
    }
    else{ 
        // There's nothing to do
    }

    RhythmUpdateArray();
    input.shouldShow = !input.shouldShow;
}
