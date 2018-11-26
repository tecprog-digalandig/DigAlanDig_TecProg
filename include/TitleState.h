#ifndef TITLESTATE_H
#define TITLESTATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "State.h"
#include "TileSet.h"

class TitleState : public State {
  public:
    TitleState();
    ~TitleState() {}
    void loadAssets();
    void update(float dt);
    void render() const;
    void rhythmUpdate();
    void start();
    void Pause() {}
    void Resume() {}
};

#endif
