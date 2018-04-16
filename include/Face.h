#ifndef FACE_H
#define FACE_H
#include "Component.h"

class Face : public Component {
  public:
    Face(GameObject& associated)
        : Component(associated), hitpoints(hitpoints_max) {}

    void Damage(int damage);

    void Update(float dt) {}
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("Face"); }

  private:
    static const int hitpoints_max = 30;
    int hitpoints = hitpoints_max;
};

#endif  // FACE_H
