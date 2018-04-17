#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "TileSet.h"

class State {
  public:
    State();
    ~State() { objectArray.clear(); }
    bool QuitRequested() const { return quitRequested; }
    void LoadAssets();
    void Update(float dt);
    void Render() const;

  private:
    void AddObject(int mouseX, int mouseY);

    // Sprite* bg;
    Music* music;
    TileSet* tileSet;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    InputManager& input;
};
