#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "GameObject.h"

class GameObject;

class Component {
  public:
    explicit Component(GameObject& associated) : associated(associated) {}
    virtual ~Component() {}

    virtual void Update(float dt) = 0;
    virtual void RhythmUpdate() = 0;
    virtual void RhythmReset() {}
    virtual void Render() const = 0;
    virtual bool Is(const std::string& type) const = 0;
    virtual void Start() {}

    virtual void NotifyCollision(std::shared_ptr<GameObject> other) {}

  protected:
    GameObject& associated;
};

#endif  // COMPONENT_H
