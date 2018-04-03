#pragma once
#include <iostream>
#include "Music.h"
#include "Sprite.h"

class State {
  public:
    State(void);
    ~State(void);
    bool QuitRequested(void);
    void LoadAssets(void);
    void Update(float dt);
    void Render(void);

  private:
    Sprite* bg;
    Music* music;
    bool quitRequested;
};
