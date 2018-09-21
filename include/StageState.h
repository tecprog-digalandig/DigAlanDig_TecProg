#ifndef STAGESTATE_H
#define STAGESTATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "State.h"

class StageState : public State {
  public:
    StageState();
    void load_assets(); 
    void update(float dt); 
    void rhythm_update(); 
    void rhythm_reset(); 
    void render() const; 
    void start(); 
    void pause() {} 
    void resume() {} 

  private:
    static void no_effect(void *udata, Uint8 *stream, int len); 
    static int count;
    static bool beat;
    static int time_rhythm; 
    int half_beat_counter = 0; 
};

#endif
