#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite, int frameCount,
               float frameTime)
    : Component(associated), damage(damage), distanceLeft(maxDistance) {
    associated.AddComponent(
        (Component*)new Sprite(associated, sprite, frameCount, frameTime));
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
