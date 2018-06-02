#ifndef BIGALAN_H
#define BIGALAN_H
#include "Component.h"

class BigAlan : public Component {
  public:
    BigAlan(GameObject& associated) : Component(associated) {}

    void Update(float dt) {}
    void RhythmUpdate() {
        associated.box.y += offset;
        offset = -offset;
    }
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("BigAlan"); }

  private:
    int offset = 20;
};

#endif  // BIGALAN_H
