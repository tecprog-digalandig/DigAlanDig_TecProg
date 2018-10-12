#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "Common.h"
#include "GameObject.h"

class GameObject;

class Component {
  public:
    explicit Component(GameObject& associated) : associated(associated) {}
    virtual ~Component() {}

    virtual void Update(float dt) = 0;
    virtual void RhythmUpdate() = 0;
    virtual void RhythmReset() {}
    virtual void Render(Common::Layer layer) const = 0;
    virtual void Start() {}

  protected:
    GameObject& associated;
};

#endif  // COMPONENT_H
