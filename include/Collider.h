#ifndef COLLIDER_H
#define COLLIDER_H
#include "Collision.h"
#include "Component.h"
#include "Rect.h"
#include "Vec2.h"

class Collider : public Component {
  public:
    Collider(GameObject& associated, Vec2 scale = Vec2(1, 1),
             Vec2 offset = Vec2())
        : Component(associated),
          box(associated.box),
          scale(scale),
          offset(offset) {}

    Rect box;

    void Update(float dt);
    void Render() const;
    bool Is(const std::string& type) const { return !type.compare("Collider"); }

    void SetScale(const Vec2& scale) { this->scale = scale; }
    void SetOffset(const Vec2& offset) { this->offset = offset; }

  private:
    Vec2 scale, offset;
};

#endif  // COLLIDER_H
