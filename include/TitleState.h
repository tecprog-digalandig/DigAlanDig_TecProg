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
    void addBackgroud(GameObject* initial_layout);
    void addMovingSpace(GameObject* initial_layout);
    void addFirstCloud(GameObject* initial_layout);
    void addSecoundCloud(GameObject* initial_layout);
    void addThirdCloud(GameObject* initial_layout);
    void addTitle(GameObject* initial_layout);
    void addPressSpace(GameObject* initial_layout);
    void addSpaceship(GameObject* initial_layout); 
    void positionComponentsMenu(GameObject *initial_layout, float position_x, float position_y);   

};

#endif
