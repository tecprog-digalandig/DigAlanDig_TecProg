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
    void Update(float dt);
    void RhythmUpdate();
    void RhythmReset();
    void Render() const;
    void Start();
    void Pause() {}
    void Resume() {}

  private:
    static void noEffect(void *udata, Uint8 *stream, int len);
    static int count;
    static bool beat;
    static int timeRhythm;
    int halfBeatCounter = 0;
};

#endif
