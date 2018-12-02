#include "StageState.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>

StageState::StageState() {}

int StageState::count = 0;
int StageState::timeRhythm = 0;
bool StageState::beat = false;


void StageState::noEffect(void *udata, Uint8 *stream, int len) {
    static constexpr float bitPBeat = 44100 * (120 / 60);
    static constexpr float halfBitPBeat = bitPBeat / 2;

    count += len;
    if (count >= halfBitPBeat) {
        beat = true;
        count -= halfBitPBeat;
        timeRhythm = SDL_GetTicks();
    }
}

void StageState::loadAssets() {
    Camera::offset.Set(-(Camera::screenSize.x - 812), 0);
    input.title = false;

    // BG
    GameObject *backG = new GameObject(Common::Layer::BG);
    createBackgroundStage("assets/img/bg1.png", 0.1, backG); //T36
    createBackgroundStage("assets/img/bg2.png", 0.3, backG); //T36
    createBackgroundStage("assets/img/bg3.png", 0.5, backG); //T36
    createBackgroundStage("assets/img/bg4.png", 0.7, backG); //T36
    createBackgroundStage("assets/img/bg5.png", 0.9, backG); //T36

    // TileMap
    GameObject *gm =
        new GameObject(Common::Layer::DEFAULT | Common::Layer::LIGHT);
    objectArray.emplace_back(gm);
    tileMap = new TileMap(*gm, "assets/map/manager.json", true);
    gm->AddComponent(tileMap);

    Game::GetInstance()->GetGridControl()->SetTileMap(tileMap);

    // Alan
    GameObject *alanGO = new GameObject();
    Vec2 gp(3, 0);
    alanGO->box.x = (gp.x * GetGridSize()) - GetGridSize() / 2;
    alanGO->box.y = (gp.y * GetGridSize()) - GetGridSize() / 2;
    alanGO->gridPosition = gp;
    objectArray.emplace_back(alanGO);

    Game::GetInstance()->GetGridControl()->SetAlan(GetObjectPrt(alanGO));

    alanGO->AddComponent(
        new Sprite(*alanGO, "assets/img/alan/idle.png", 2, 0.2));
    alanGO->AddComponent(new Sound(*alanGO));

    Alan *lilAlan = new Alan(*alanGO);
    alanGO->AddComponent(lilAlan);

    alanGO->AddComponent(new Interpol(*alanGO));
    alanGO->AddComponent(new AlanAnimation(*alanGO));
    alanGO->AddComponent(new AlanActionControl(*alanGO, GetGridSize()));

    GameObject *alanL = new GameObject(Common::Layer::LIGHT);
    objectArray.emplace_back(alanL);
    alanL->AddComponent(new Light(*alanL, GetObjectPrt(alanGO)));

    Camera::Follow(alanGO);

    GameObject *esGO = new GameObject();
    esGO->AddComponent(new EnemySpawn(*esGO, tileMap));
    objectArray.emplace_back(esGO);

    GameObject *frameG = new GameObject(Common::Layer::HUD);
    positionComponent(frameG, 0, 0);; //T36
    frameG->AddComponent(new bgCircularY(*frameG, "assets/img/framebg.png"));
    frameG->AddComponent(new ParallaxY(*frameG, 1));

    // MiniMap
    createMiniMap(alanGO, tileMap); //T36
    
    // Big-Alan
    createBigAlan(); //T36
    
    // HUD
    createTimerHud(); //T36
    createMeterHeart(alanGO); //T36
    createMeterLight(alanGO); //T36
    createCounterMetal(); //T36
    createCounterCristal(); //T36
    createCounterPetro(); //T36
    createItemCount(lilAlan); //T36
    
    // Music
    music.Open("assets/audio/marmota.ogg");
    count = 0;
    halfBeatCounter = 0;
    Mix_SetPostMix(noEffect, NULL);
}

void StageState::createBackgroundStage(string image, float velocity, GameObject *backG) { //T36
    //T34
    backG = new GameObject(Common::Layer::BG);
    positionComponent(backG, 212, 0); //T36
    backG->AddComponent(new bgCircularY(*backG, image));
    backG->AddComponent(new ParallaxY(*backG, velocity));
}    

void StageState::positionComponent(GameObject *component, float positionX, float positionY){ //T36
    //T34
    objectArray.emplace_back(component);
    component->world_reference = false;
    component->box.pos = {positionX, positionY};
}

void StageState::createTimerHud(){ //T36
    //T34
    GameObject *timerHud = new GameObject(Common::Layer::HUD);
    positionComponent(timerHud, 212 + 600 / 2, Camera::screenSize.y - 50); //T36
    timerHud->AddComponent(new HudTimer(*timerHud));

}

void StageState::createMeterHeart(GameObject *alanGO){ //T36
    //T34
    GameObject *meterHeart = new GameObject(Common::Layer::HUD);
    positionComponent(meterHeart, 30, 30); //T36
    meterHeart->AddComponent(new HeartMeter(
        *meterHeart, "assets/hud/barravida.png", "assets/hud/coracao.png"));
    meterHeart->GetComponent<HeartMeter *>()->setIsHeart(true);
    meterHeart->GetComponent<HeartMeter *>()->SetAlan(GetObjectPrt(alanGO));
}

void StageState::createMeterLight(GameObject *alanGO){ //T36
    //T34
    GameObject *meterLight = new GameObject(Common::Layer::HUD);
    positionComponent(meterLight, 30, 100); //T36
    meterLight->AddComponent(new LightMeter(
        *meterLight, "assets/hud/barraluz.png", "assets/hud/raio.png"));
    meterLight->GetComponent<LightMeter *>()->setIsHeart(false);
    meterLight->GetComponent<LightMeter *>()->SetAlan(GetObjectPrt(alanGO));
}

void StageState::createCounterMetal(){ //T36
    //T34
    GameObject *counterMetal = new GameObject(Common::Layer::HUD);
    positionComponent(counterMetal, 850, 10); //T36
    counterMetal->AddComponent(new HudCounter(
        *counterMetal, "assets/hud/item1.png", "assets/hud/metali.png"));

}

void StageState::createCounterCristal(){ //T36
    //T34
    GameObject *counterCristal = new GameObject(Common::Layer::HUD);
    positionComponent(counterCristal, 850, 160); //T36
    counterCristal->AddComponent(new HudCounter(
        *counterCristal, "assets/hud/item2.png", "assets/hud/cristali.png"));
}

void StageState::createCounterPetro(){ //T36
    //T34
    GameObject *counterPetro = new GameObject(Common::Layer::HUD);
    positionComponent(counterPetro, 850, 310); //T36
    counterPetro->AddComponent(new HudCounter(
        *counterPetro, "assets/hud/item3.png", "assets/hud/petroleoi.png"));
}

void StageState::createItemCount(Alan *lilAlan){ //T36
    //T34
    GameObject *itemCount = new GameObject(Common::Layer::HUD);
    objectArray.emplace_back(itemCount);
    itemCount->world_reference = false;
    itemCount->AddComponent(new AlanItemCount(*itemCount));
    lilAlan->SetItemCount(itemCount);
}

void StageState::createBigAlan(){ //T36
    //T34
    GameObject *bigAlan = new GameObject(Common::Layer::HUD);
    positionComponent(bigAlan, 0, Camera::screenSize.y - bigAlan->box.h); //T36
    bigAlan->AddComponent(new Sprite(*bigAlan, "assets/img/mooda.png", 2, -1));
    bigAlan->AddComponent(new BigAlan(*bigAlan));
}

void StageState::createMiniMap(GameObject *alanGO, TileMap *tileMap){ //T36
    //T34
    GameObject *MiniMapTile = new GameObject(Common::Layer::HUD);
    positionComponent(MiniMapTile, 30, 180); //T36
    MiniMapTile->AddComponent(
        new Sprite(*MiniMapTile, "assets/img/bgminimap.png"));

    MiniMapTile = new GameObject(Common::Layer::HUD);
    positionComponent(MiniMapTile, 60, 195); //T36
    TileSet *minitileSet = new TileSet("assets/map/miniground.json");
    MiniTileMap *miniTilemap = new MiniTileMap(*MiniMapTile, minitileSet,
                                               tileMap, GetObjectPrt(alanGO));
    MiniMapTile->AddComponent(miniTilemap);
}

void StageState::start() {
    if (!started) loadAssets();

    StartArray();
}

void StageState::update(float dt) {
    Camera::update(dt);

    if (beat) {
        beat = false;
        static constexpr float bpm = 120;
        static const int beatTime = (60 * 1000) / bpm;
        static const int halfBeatTime = beatTime / 2;

        if (halfBeatCounter == 0) Game::GetInstance()->StartBeatTime();

        Game::GetInstance()->UpdateBeatTime(halfBeatCounter * halfBeatTime);
        halfBeatCounter++;
    }
    UpdateArray(dt);
}

void StageState::rhythmUpdate() {
    if (!musicPlaying) {
        music.Play();
        musicPlaying = true;
    }
    RhythmUpdateArray();
}

void StageState::RhythmReset() { RhythmResetArray(); }

void StageState::render() const { RenderArray(); }
