#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "State.h"
#include "Vec2.h"

class PenguinCannon : public Component {
  public:
    PenguinCannon(GameObject& associated,
                  std::weak_ptr<GameObject> penguinbody);

    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const {
        return !type.compare("PenguinCannon");
    }

    void Start() {}
    void Shoot();

  private:
    std::weak_ptr<GameObject> pbody;
    float angle = 0;

    static constexpr float bulletSpeed = 200;
    static constexpr float maxDistance = 600;
    static const int minionDist = 150;
    static const int damage = 50;
    static const int distCannon = 53;

    InputManager& input;
    Vec2 t;
};

#endif  // PENGUINCANNON_H
