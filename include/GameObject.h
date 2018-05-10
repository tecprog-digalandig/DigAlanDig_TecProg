#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <algorithm>
#include <memory>
#include <vector>
#include "Component.h"
#include "Rect.h"

class Component;

class GameObject {
  public:
    GameObject() : isDead(false) {}
    ~GameObject();

    void Update(float dt);
    void Render(void);
    // REMOVE
    bool CanEnd() const;

    bool IsDead(void) const { return isDead; }
    void RequestDelete(void) { isDead = true; }
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetComponent(const std::string &type) const;
    void Start();
    void NotifyCollision(std::shared_ptr<GameObject> other);

    double AngleRad() { return angleDeg * M_PI / 180; }

    Rect box;
    bool worldReference = true;
    bool fromPlayer = false;
    bool started = false;
    double angleDeg = 0;

  private:
    std::vector<Component *> components;
    bool isDead;
};

#endif  // GAMEOBJECT_H
