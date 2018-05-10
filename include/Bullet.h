#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "GameObject.h"

class Bullet : public Component {
  public:
    Bullet(GameObject& associated, float angle, float speed, int damage,
           float maxDistance, std::string sprite, int frameCount = 1,
           float frameTime = 1);
    void Update(float dt);
    void Render() const {}
    bool Is(const std::string& type) const { return !type.compare("Bullet"); }

    int GetDamage() { return damage; }

    void NotifyCollision(std::shared_ptr<GameObject> other);

  private:
    int damage;
    float maxTime = 3;
    Vec2 speed;
    float distanceLeft;
};

#endif  // BULLET_H
