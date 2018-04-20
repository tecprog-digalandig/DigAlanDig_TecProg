#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <algorithm>
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
    void AddComponent(Component *cpt) { components.emplace_back(cpt); }
    void RemoveComponent(Component *cpt);
    Component *GetComponent(const std::string &type) const;

    Rect box;
    bool worldReference = true;

  private:
    std::vector<Component *> components;
    bool isDead;
};

#endif  // GAMEOBJECT_H
