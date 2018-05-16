#ifndef STAGESTATE_H
#define STAGESTATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "State.h"
#include "TileSet.h"

class StageState : public State {
  public:
    StageState();
    ~StageState() { delete music; }
    void LoadAssets();
    void Update(float dt);
    void Render() const;
    void Start();
    void Pause() {}
    void Resume() {}

  private:
    Music* music = nullptr;
    TileSet* tileSet = nullptr;
};

#endif
