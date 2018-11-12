#include "StageState.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>
#include "Alan.h"
#include "AlanActionControl.h"
#include "AlanAnimation.h"
#include "AlanItemCount.h"
#include "BigAlan.h"
#include "Camera.h"
#include "EnemySpawn.h"
#include "Game.h"
#include "HudCounter.h"
#include "HudMeter.h"
#include "HudTimer.h"
#include "Interpol.h"
#include "Light.h"
#include "MiniTileMap.h"
#include "Parallax.h"
#include "Sound.h"
#include "Sprite.h"
#include "Vec2.h"

StageState::StageState() {}

int StageState::count = 0;
int StageState::time_rhythm = 0; 
bool StageState::beat = false;

void StageState::noeffect(void *udata, Uint8 *stream, int len) { 
    static constexpr float bit_p_beat = 44100 * (120 / 60); 
    static constexpr float half_bit_p_beat = bit_p_beat / 2; 

    count += len;
    if (count >= half_bit_p_beat) { 
        beat = true;
        count -= half_bit_p_beat; 
        time_rhythm = SDL_GetTicks(); 
    }
}

void StageState::loadAssets() {
    Camera::offset.Set(-(Camera::screenSize.x - 812), 0);
    input.title = false;

    // BG
    GameObject *backG = new GameObject(Common::Layer::BG);
    backG->world_reference = false;
    objectArray.emplace_back(backG);
    backG->addComponent(new bgCircularY(*backG, "assets/img/bg1.png"));
    backG->addComponent(new ParallaxY(*backG, 0.1));
    backG->box.pos = {212, 0};

    backG = new GameObject(Common::Layer::BG);
    backG->world_reference = false;
    objectArray.emplace_back(backG);
    backG->addComponent(new bgCircularY(*backG, "assets/img/bg2.png"));
    backG->addComponent(new ParallaxY(*backG, 0.3));
    backG->box.pos = {212, 0};

    backG = new GameObject(Common::Layer::BG);
    backG->world_reference = false;
    objectArray.emplace_back(backG);
    backG->addComponent(new bgCircularY(*backG, "assets/img/bg3.png"));
    backG->addComponent(new ParallaxY(*backG, 0.5));
    backG->box.pos = {212, 0};

    backG = new GameObject(Common::Layer::BG);
    backG->world_reference = false;
    objectArray.emplace_back(backG);
    backG->addComponent(new bgCircularY(*backG, "assets/img/bg4.png"));
    backG->addComponent(new ParallaxY(*backG, 0.7));
    backG->box.pos = {212, 0};

    backG = new GameObject();
    backG->world_reference = false;
    objectArray.emplace_back(backG);
    backG->addComponent(new bgCircularY(*backG, "assets/img/bg5.png"));
    backG->addComponent(new ParallaxY(*backG, 0.9));
    backG->box.pos = {212, 0};

    // TileMap
    GameObject *gm =
        new GameObject(Common::Layer::DEFAULT | Common::Layer::LIGHT);
    objectArray.emplace_back(gm);
    tileMap = new TileMap(*gm, "assets/map/manager.json", true);
    gm->addComponent(tileMap);

    Game::getInstance()->getGridControl()->SetTileMap(tileMap);

    // Alan
    GameObject *alan_go = new GameObject(); 
    Vec2 gp(3, 0);
    alan_go->box.x = (gp.x * GetGridSize()) - GetGridSize() / 2; 
    alan_go->box.y = (gp.y * GetGridSize()) - GetGridSize() / 2; 
    alan_go->gridPosition = gp; 
    object_array.emplace_back(alan_go); 

    Game::getInstance()->getGridControl()->SetAlan(GetObjectPrt(alanGO));

    alanGO->addComponent(
        new Sprite(*alanGO, "assets/img/alan/IDLE.png", 2, 0.2));
    alanGO->addComponent(new Sound(*alanGO));

    Alan *lilAlan = new Alan(*alanGO);
    alanGO->addComponent(lilAlan);

    alanGO->addComponent(new Interpol(*alanGO));
    alanGO->addComponent(new AlanAnimation(*alanGO));
    alanGO->addComponent(new AlanActionControl(*alanGO, GetGridSize()));

    GameObject *alanL = new GameObject(Common::Layer::LIGHT);
    objectArray.emplace_back(alanL);
    alanL->addComponent(new Light(*alanL, GetObjectPrt(alanGO)));

    GameObject *es_go = new GameObject(); 
    es_go->add_component(new EnemySpawn(*es_go, tile_map)); 
    object_array.emplace_back(es_go); 

    GameObject *esGO = new GameObject();
    esGO->addComponent(new EnemySpawn(*esGO, tileMap));
    objectArray.emplace_back(esGO);

    GameObject *frameG = new GameObject(Common::Layer::HUD);
    frameG->world_reference = false;
    objectArray.emplace_back(frameG);
    frameG->addComponent(new bgCircularY(*frameG, "assets/img/framebg.png"));
    frameG->addComponent(new ParallaxY(*frameG, 1));
    frameG->box.pos = {0, 0};

    // MiniMap
    GameObject *MiniMapTile = new GameObject(Common::Layer::HUD);
    MiniMapTile->world_reference = false;
    MiniMapTile->box.pos = {30, 180};
    MiniMapTile->addComponent(
        new Sprite(*MiniMapTile, "assets/img/bgminimap.png"));
    objectArray.emplace_back(MiniMapTile);

    MiniMapTile = new GameObject(Common::Layer::HUD);
    MiniMapTile->box.pos = {60, 195};
    TileSet *minitileSet = new TileSet("assets/map/miniground.json");
    MiniTileMap *miniTilemap = new MiniTileMap(*MiniMapTile, minitileSet,
                                               tileMap, GetObjectPrt(alanGO));
    MiniMapTile->addComponent(miniTilemap);
    objectArray.emplace_back(MiniMapTile);

    // Big-Alan
    GameObject *bigAlan = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(bigAlan);
    bigAlan->addComponent(new Sprite(*bigAlan, "assets/img/mooda.png", 2, -1));
    bigAlan->addComponent(new BigAlan(*bigAlan));
    bigAlan->world_reference = false;
    bigAlan->box.pos = {0, Camera::screenSize.y - bigAlan->box.h};

    // HUD
    GameObject *timerHud = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(timerHud);
    timerHud->world_reference = false;
    timerHud->box.pos = {212 + 600 / 2, Camera::screenSize.y - 50};
    timerHud->addComponent(new HudTimer(*timerHud));

    GameObject *meterHeart = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(meterHeart);
    meterHeart->world_reference = false;
    meterHeart->box.pos = {30, 30};
    meterHeart->addComponent(new HeartMeter(
        *meterHeart, "assets/hud/barravida.png", "assets/hud/coracao.png"));
    meterHeart->GetComponent<HeartMeter *>()->setIsHeart(true);
    meterHeart->GetComponent<HeartMeter *>()->SetAlan(GetObjectPrt(alanGO));

    GameObject *meterLight = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(meterLight);
    meterLight->world_reference = false;
    meterLight->box.pos = {30, 100};
    meterLight->addComponent(new LightMeter(
        *meterLight, "assets/hud/barraluz.png", "assets/hud/raio.png"));
    meterLight->GetComponent<LightMeter *>()->setIsHeart(false);
    meterLight->GetComponent<LightMeter *>()->SetAlan(GetObjectPrt(alanGO));

    GameObject *counterMetal = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(counterMetal);
    counterMetal->world_reference = false;
    counterMetal->box.pos = {850, 10};
    counterMetal->addComponent(new HudCounter(
        *counterMetal, "assets/hud/item1.png", "assets/hud/metali.png"));

    GameObject *counterCristal = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(counterCristal);
    counterCristal->world_reference = false;
    counterCristal->box.pos = {850, 160};
    counterCristal->addComponent(new HudCounter(
        *counterCristal, "assets/hud/item2.png", "assets/hud/cristali.png"));

    GameObject *counterPetro = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(counterPetro);
    counterPetro->world_reference = false;
    counterPetro->box.pos = {850, 310};
    counterPetro->addComponent(new HudCounter(
        *counterPetro, "assets/hud/item3.png", "assets/hud/petroleoi.png"));

    GameObject *item_count = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(item_count);
    item_count->world_reference = false;
    item_count->addComponent(new AlanItemCount(*item_count));
    lilAlan->setItemCount(item_count);

    // Music
    music.isOpen("assets/audio/marmota.ogg");
    count = 0;
    half_beat_counter = 0;
    Mix_SetPostMix(no_effect, NULL);
}

void StageState::Start() {
    if (!started) loadAssets();

    start_array();
}

void StageState::Update(float delta_time) {
    Camera::Update(delta_time);

    if (beat) {
        beat = false;
        static constexpr float bpm = 120;
        static const int beat_time = (60 * 1000) / bpm;
        static const int half_beat_time = beat_time / 2;

        if (halfBeatCounter == 0) Game::getInstance()->StartBeatTime();

        Game::getInstance()->UpdateBeatTime(halfBeatCounter * half_beat_time);
        halfBeatCounter++;
    }
    ypdateArray(delta_time);
}

void StageState::rhythmUpdate() {
    if (!musicPlaying) {
        music.play_func();
        musicPlaying = true;
    }
    rhythmUpdateArray();
}

void StageState::rhythm_reset() { rhythm_reset_array(); }

void StageState::render() const { RenderArray(); }
