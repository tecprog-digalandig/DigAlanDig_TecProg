#ifndef STAGESTATE_H
#define STAGESTATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "State.h"
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


class StageState : public State {
  public:
    StageState();
    void loadAssets();
    void update(float dt);
    void rhythmUpdate();
    void RhythmReset();
    void render() const;
    void start();
    void createBackgroundStage(string image, float velocity, GameObject *backG);
    void positionComponent(GameObject *component, float positionX, float positionY);
    void Pause() {}
    void createTimerHud();
    void createMeterHeart(GameObject *alanGO);
    void createMeterLight(GameObject *alanGO);
    void createCounterMetal();
    void createCounterCristal();
    void createCounterPetro();
    void createItemCount(Alan *lilAlan);
    void createBigAlan();
    void createMiniMap(GameObject *alanGO, TileMap *tileMap);
    void Resume() {}

  private:
    static void noEffect(void *udata, Uint8 *stream, int len);
    static int count;
    static bool beat;
    static int timeRhythm;
    int halfBeatCounter = 0;
};

#endif
