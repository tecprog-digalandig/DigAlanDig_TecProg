#ifndef ALIEN_H
#define ALIEN_H
#include <memory>
#include <queue>
#include <vector>
#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"

class Alien : public Component {
  public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("Alien"); }

  private:
    class Action {
      public:
        enum ActionType { MOVE, SHOOT };
        Action(ActionType type, float x, float y) : type(type), pos(x, y) {}
        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp = maxHp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;

    InputManager& input;
    static const int maxSpeed = 100;
    static const int maxHp = 100;
};

#endif  // ALIEN_H
