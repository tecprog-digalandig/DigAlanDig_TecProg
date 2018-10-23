#ifndef INTERPOL_H
#define INTERPOL_H

#include <iostream>
#include <string>
#include "Component.h"
#include "Vec2.h"

class Interpol : public Component {
  public:
    explicit Interpol(GameObject &associated);

    void update(float delta_time);
    void rhythmUpdate() {}
    void RhythmReset() {}
    void render(Common::Layer layer) const {}
    void Start() {}

    bool isMovementDone() { return movementDone; }

    Vec2 target;
    bool isHit = false;

  private:
    Vec2 alanPos;
    bool movementDone = true;
    Vec2 speed;
};

#endif  // INTERPOL_H
