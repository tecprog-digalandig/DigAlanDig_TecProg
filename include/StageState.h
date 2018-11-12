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
    void loadAssets();
    void update(float delta_time);
    void rhythmUpdate();
    void RhythmReset();
    void render() const;
    void start();
    void Pause() {}
    void Resume() {}

  private:
    static void no_effect(void *udata, Uint8 *stream, int len); 
    static int count;
    static bool beat;
    static int time_rhythm; 
    int half_beat_counter = 0; 
};

#endif
