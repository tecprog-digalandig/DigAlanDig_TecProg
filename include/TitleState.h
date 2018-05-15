#ifndef TITLESTATE_H
#define TITLESTATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "State.h"
#include "TileSet.h"

class TitleState : public State {
  public:
    TitleState();
    ~TitleState() {}
    void LoadAssets();
    void Update(float dt);
    void Render() const;
    void Start();
    void Pause() {}
    void Resume() {}
};

#endif
