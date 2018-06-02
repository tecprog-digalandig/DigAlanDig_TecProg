#ifndef ALAN_H
#define ALAN_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include <iostream>
#include <queue>
#include <string>
#include "Component.h"
#include "InputManager.h"
#include "SDL_include.h"
#include "TileMap.h"
#include "Vec2.h"

class Alan : public Component {
  public:
    Alan(GameObject& associated, Vec2 gridPosition, int gridSizeHeight,
         int gridSizeWidth);

    ~Alan() {}

    void GetMovement();

    void Update(float dt);
    void RhythmUpdate() {}
    void RhythmReset() { moved = false; }
    void Render() const {}
    bool Is(const std::string& type) const {
        return !type.compare("PenguinBody");
    }

    Vec2 GetGridPosition() { return gridPosition; }

  private:
    enum Direction { NONE = 0, UP, DOWN, LEFT, RIGHT };
    int gridSizeWidth;
    int gridSizeHeight;
    Direction movementDirection;

    Vec2 gridPosition;
    int frameNumber = 0;

    InputManager& input;

    bool moved = false;
};

#endif  // ALAN_H
