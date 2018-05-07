#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg)
    : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg) {
    associated.AddComponent(
        (Component *)new Sprite(associated, "assets/img/minion.png"));
}

void Minion::Update(float dt) {
    arc += rotSpeed * dt;

    if (auto alien = alienCenter.lock())
        associated.box.SetCenter(alien->box.Center() +
                                 Vec2(minionDist, 0).RotateRad(arc));
    else
        associated.RequestDelete();
}
