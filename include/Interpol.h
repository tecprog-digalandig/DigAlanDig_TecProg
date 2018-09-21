#ifndef INTERPOL_H
#define INTERPOL_H

#include <iostream>
#include <string>
#include "Component.h"
#include "Vec2.h"

class Interpol : public Component {
  public:
    explicit Interpol(GameObject &associated);

    void update(float dt);
    void rhythmUpdate() {}
    void RhythmReset() {}
    void render(Common::Layer layer) const {}
    void start() {}

    bool IsMovementDone() { return movementDone; }

    Vec2 target;
    bool isHit = false;

  private:
    Vec2 alanPos;
    bool movementDone = true;
    Vec2 speed;
};

#endif  // INTERPOL_H
