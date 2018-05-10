#ifndef PENGUINBODY_H
#define PENGUINBODY_H
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PenguinCannon.h"
#include "State.h"
#include "Vec2.h"

class PenguinBody : public Component {
  public:
    PenguinBody(GameObject& associated);
    ~PenguinBody() { player = nullptr; }

    void Start();
    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const {
        return !type.compare("PenguinBody");
    }
    Vec2 GetSpeed() const { return speed; }
    void TakeDamage(int damage) { hp -= damage; }
    void NotifyCollision(std::shared_ptr<GameObject> other);

    PenguinBody* player;

  private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed = 0;
    float angle = -90;
    int hp = maxHp;
    static const int maxHp = 100;
    static constexpr float accel = 150;
    static constexpr float minSpeed = -200;
    static constexpr float maxSpeed = 300;
    static constexpr float rotSpeed = 90;
    static constexpr float drag = 0.25;

    InputManager& input;
};

#endif  // PENGUINBODY_H
