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
         NONE = 0, up, down, left, right
    };

    enum Action 
    { 
        standin = 0, walkin, climbin, fallin_var
    };

    AlanActionControl(GameObject& associated, int grid_size)
        : Component(associated),
          input(InputManager::getInstance()),
          grid_size(grid_size) {}

    ~AlanActionControl() {}

    void fallin(float delta_time);

    bool shouldFall();

    bool canClimb();

    bool inClimbPosition(AlanAnimation* animation);

    bool climbPathFree();

    bool isBlock();

    bool isFree();

    bool isClimbDirectionleft(AlanAnimation* animation);

    void update(float delta_time);

    void rhythmUpdate() {}

    void rhythmReset() {}

    void render(Common::Layer layer) const {}
    
    bool isMovementDone() 
    { 
        return !animation_on_going; 
    }

    AlanActionControl::Direction getMovementDirection() 
    {
        return movement_direction;
    }

    void setMovementDirection(Direction movementDirection) 
    {
        this->movement_direction = movement_direction;
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
    Direction movement_direction = Direction::NONE;
    Action action = Action::standin;
    int grids_left = 0;

    InputManager& input;

    int grid_size;

    bool moved = false;
    bool animation_on_going = false;
};

#endif  // ALANACTIONCONTROL_H
