#ifndef INTERPOL_H
#define INTERPOL_H

#include <iostream>
#include <string>
#include "Component.h"
#include "Vec2.h"

class Interpol : public Component
{
  public:
    explicit Interpol(GameObject &associated);

    void Update(float delta_time);
    void rhythmUpdate() {}
    void RhythmReset() {}
    void render(Common::Layer layer) const {}
    void Start() {}

    bool isMovementDone() { return movementDone; }

    Vec2 target;
    bool is_hit = false;

  private:
    Vec2 alan_pos;
    bool movement_done = true;
    Vec2 speed;
};

#endif  // INTERPOL_H
