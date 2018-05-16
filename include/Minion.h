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

    void NotifyCollision(std::shared_ptr<GameObject> other);
    void Shoot(Vec2 target) const;

  private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;

    static constexpr float rotSpeed = M_PI / 4;
    static constexpr float bulletSpeed = 200;
    static constexpr float maxDistance = 500;
    static const int minionDist = 150;
    static const int damage = 50;
};

#endif  // MINION_H
