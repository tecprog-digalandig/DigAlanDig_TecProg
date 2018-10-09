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

class AlanActionControl : public Component {
  public:
    enum Direction { NONE = 0, UP, DOWN, LEFT, RIGHT };
    enum Action { STANDIN = 0, WALKIN, CLIMBING, FALLIN };

    AlanActionControl(GameObject& associated, int gridSize)
        : Component(associated),
          input(InputManager::GetInstance()),
          gridSize(gridSize) {}

    ~AlanActionControl() {}

    void Fallin(float dt);

    bool ShouldFall();

    bool CanClimb();
    bool InClimbPosition(AlanAnimation* animation);
    bool ClimbPathFree();

    bool IsBlock();
    bool IsFree();

    bool IsClimbDirectionLeft(AlanAnimation* animation);

    void update(float dt);
    void rhythmUpdate() {}
    void RhythmReset() {}
    void render(Common::Layer layer) const {}

    bool IsMovementDone() { return !animationOnGoing; }

    AlanActionControl::Direction GetMovementDirection() {
        return movementDirection;
    }
    void SetMovementDirection(Direction movementDirection) {
        this->movementDirection = movementDirection;
    }
    void SetAction(Action action) { this->action = action; }
    Action GetAction() { return action; }

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
