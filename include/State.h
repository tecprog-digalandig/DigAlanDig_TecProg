#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"

class State {
  public:
    State();
    ~State() { objectArray.clear(); }
    bool QuitRequested() { return quitRequested; }
    void LoadAssets();
    void Update(float dt);
    void Render();

  private:
    void Input();
    void AddObject(int mouseX, int mouseY);

    // Sprite* bg;
    Music* music;
    TileSet* tileSet;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};
