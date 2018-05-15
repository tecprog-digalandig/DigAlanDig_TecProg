#include "Bullet.h"
#include "Collider.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite, int frameCount,
               float frameTime)
    : Component(associated), damage(damage), distanceLeft(maxDistance) {
    associated.AddComponent(
        new Sprite(associated, sprite, frameCount, frameTime));
    associated.AddComponent(new Collider(associated));

    associated.angleDeg = angle;
    this->speed = Vec2(speed).Rotate(angle);
    associated.box.SetCenter(associated.box.pos);
}

void Bullet::Update(float dt) {
    if (distanceLeft <= 0 || maxTime <= 0) {
        associated.RequestDelete();
        return;
    }
    Vec2 move = speed * dt;
    distanceLeft -= move.Length();
    associated.box.pos += move;

    maxTime -= dt;
}

void Bullet::NotifyCollision(std::shared_ptr<GameObject> other) {
    if (associated.fromPlayer == other->fromPlayer) return;

    std::cout << "Collision Bullet" << std::endl;
    if (other->GetComponent<Bullet*>()) return;

    associated.RequestDelete();
}
