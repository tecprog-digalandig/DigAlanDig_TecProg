#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite)
    : Component(associated), damage(damage), distanceLeft(maxDistance) {
    // speed
    associated.AddComponent((Component*)new Sprite(associated, sprite));
    associated.angleDeg = 180 * angle * M_1_PI;
    this->speed = Vec2(speed, 0).RotateRad(angle);
}

void Bullet::Update(float dt) {
    if (distanceLeft <= 0) {
        associated.RequestDelete();
        return;
    }
    Vec2 move = speed * dt;
    distanceLeft -= move.Length();
    associated.box.pos += move;
}
