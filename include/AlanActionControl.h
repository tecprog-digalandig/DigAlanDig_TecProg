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
         NONE = 0, UP, DOWN, LEFT, RIGHT 
    };

    enum Action 
    { 
        STANDIN = 0, WALKIN, CLIMBING, FALLIN 
    };

    AlanActionControl(GameObject& associated, int gridSize)
        : Component(associated),
          input(InputManager::GetInstance()),
          gridSize(gridSize) {}

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
        return !animationOnGoing; 
    }

    AlanActionControl::Direction getMovementDirection() 
    {
        return movementDirection;
    }

    void setMovementDirection(Direction movementDirection) 
    {
        this->movementDirection = movementDirection;
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
    Direction movementDirection = Direction::NONE;
    Action action = Action::STANDIN;
    int gridsLeft = 0;

    InputManager& input;

    int gridSize;

    bool moved = false;
    bool animationOnGoing = false;
};

#endif  // ALANACTIONCONTROL_H
