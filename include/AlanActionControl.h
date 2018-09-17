#ifndef ALANACTIONCONTROL_H
#define ALANACTIONCONTROL_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>

#include "AlanAnimation.h"

class AlanActionControl : public Component 
{
  public:
    enum Direction 
    {
         none = 0, up, down, left, right 
    };

    enum Action 
    { 
        standin = 0, walkin, climbing, fallin 
    };

    AlanActionControl(GameObject& associated, int grid_size)
        : Component(associated),
          input(InputManager::GetInstance()),
          gridSize(grid_size) {}

    ~AlanActionControl() {}

    void fallin(float dt);

    bool shouldFall();

    bool canClimb();

    bool inClimbPosition(AlanAnimation* animation);

    bool climbPathFree();

    bool isBlock();

    bool isFree();

    bool isClimbDirectionLeft(AlanAnimation* animation);

    void update(float dt);

    void rhythmUpdate() {}

    void rhythmReset() {}

    void render(Common::Layer layer) const {}

    bool isMovementDone() 
    { 
        return !animation_on_gGoing; 
    }

    AlanActionControl::Direction getMovementDirection() 
    {
        return movement_direction;
    }

    void setMovementDirection(Direction movementDirection) 
    {
        this->movementDirection = movement_direction;
    }

    void setAction(Action action) 
    { 
        this->action = action; 
    }

    Action getAction() 
    { 
        return action; 
    }

  private:
    Direction movement_direction = Direction::none;
    Action action = Action::standin;
    int grids_left = 0;

    InputManager& input;

    int grid_size;

    bool moved = false;
    bool animation_on_going = false;
};

#endif  // ALANACTIONCONTROL_H
