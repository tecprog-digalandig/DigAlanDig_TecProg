#ifndef ALIEN_H
#define ALIEN_H
#include <memory>
#include <queue>
#include <vector>
#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "State.h"
#include "Timer.h"
#include "Vec2.h"

class Alien : public Component {
  public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("Alien"); }

    void TakeDamage(int damage) { hp -= damage; }
    void NotifyCollision(std::shared_ptr<GameObject> other);

    static int alienCount;

  private:
    Vec2 speed;
    int hp = maxHp;
    std::vector<std::weak_ptr<GameObject>> minionArray;

    enum AlienState { MOVING, RESTING };
    AlienState state = RESTING;
    Timer restTimer;
    Vec2 destination;

    std::shared_ptr<GameObject> closestMinion(const Vec2& target);
    InputManager& input;
    static const int maxSpeed = 100;
    static const int maxHp = 100;
    static constexpr float restDuration = 3;
    static constexpr float degPerS = 10;
};

#endif  // ALIEN_H
