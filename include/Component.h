#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "GameObject.h"

class GameObject;

class Component {
  public:
    Component(GameObject& associated) : associated(associated) {}
    virtual ~Component() {}

    virtual void Update(float dt) = 0;
    virtual void Render() const = 0;
    virtual bool Is(const std::string& type) const = 0;

  protected:
    GameObject& associated;
};

#endif  // COMPONENT_H
