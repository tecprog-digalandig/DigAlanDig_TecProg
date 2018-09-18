#ifndef ALANANIMATION_H
#define ALANANIMATION_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

// Class characteristics and heritages.
class AlanAnimation : public Component 
{
  public:
    enum Transition 
    {
        none_t,
        walk,
        hit_t,
        climb,
        stop_climb,
        floor,
        fall,
        dig_t,
        dance,
        die
    };

    enum Direction 
    { 
        left = 0, right, up, down
    };

    enum State 
    {
        none_s = 0,
        idle,
        walkin,
        fallin,
        dig,
        climbin,
        dig_climb,
        dancin,
        dead,
        state_max
    };

    explicit AlanAnimation(GameObject &associated);

    //Destructor.
    ~AlanAnimation();

    //Update according to dt.
	//@param dt: Delta time. Time elapsed between one frame and the other.
    void update(float dt);

    void rhythmUpdate() {}

    void render(Common::Layer layer) const {}

    void start() 
    {
        currentState = State::idle;
        oldState = current_state;
        currentDirection = left;
        oldDirection = current_direction;
    }

    void setAction(Transition trans, Direction dir);

    Direction getCurrentDirection() 
    { 
        return current_direction; 
    }

    Direction getOldDirection() 
    { 
        return old_direction; 
    }

    State getCurrentState() 
    { 
        return current_state; 
    }

    State getOldState() 
    { 
        return old_state; 
    }

  private:
    State old_state = none_s, current_state = none_s;
    Direction old_direction = left, current_direction = left;
    Sprite::SpriteState AState[State::state_max];

    void playSound(Transition trans);
};

#endif  // ALANANIMATION_H
