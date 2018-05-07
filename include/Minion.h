#ifndef MINION_H
#define MINION_H
#include <memory>
#include "Alien.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class Minion : public Component {
  public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter,
           float arcOffsetDeg = 0);

    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("Minion"); }

    void Shoot(Vec2 target);

  private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;

    static constexpr float rotSpeed = M_PI_4;
    static const int minionDist = 150;
};

#endif  // MINION_H
