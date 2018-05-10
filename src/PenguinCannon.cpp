#include "PenguinCannon.h"
#include "Bullet.h"
#include "Game.h"
#include "PenguinBody.h"
#include "Sprite.h"

PenguinCannon::PenguinCannon(GameObject& associated,
                             std::weak_ptr<GameObject> penguinbody)
    : Component(associated),
      pbody(penguinbody),
      input(InputManager::GetInstance()) {
    associated.AddComponent(
        (Component*)new Sprite(associated, "assets/img/cubngun.png"));
}

void PenguinCannon::Update(float dt) {
    if (auto p = pbody.lock())
        associated.box.SetCenter(p->box.Center());
    else
        associated.RequestDelete();

    angle = Vec2(input.GetWorldMouse() - associated.box.Center()).AngleDeg();
    associated.angleDeg = angle;

    if (input.IsMouseDown(input.mouseKey::LEFT)) Shoot();
}

void PenguinCannon::Shoot() {
    State* state = Game::getInstance()->getState();
    GameObject* gm = new GameObject();
    state->AddObject(gm);

    std::cout << associated.box.Center() << std::endl;
    gm->box.pos = associated.box.Center() + Vec2(distCannon, 0).Rotate(angle);

    Vec2 bulletMove = Vec2(bulletSpeed, 0).Rotate(angle);
    if (auto p = pbody.lock())
        if (auto body = (PenguinBody*)p->GetComponent("PenguinBody"))
            bulletMove += body->GetSpeed();

    gm->AddComponent(new Bullet(*gm, 180 * M_1_PI * bulletMove.Angle(),
                                bulletMove.Length(), damage, maxDistance,
                                "assets/img/penguinbullet.png", 4, 0.7));
}
