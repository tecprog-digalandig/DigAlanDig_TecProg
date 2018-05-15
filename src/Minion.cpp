#include "Minion.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg)
    : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg) {
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(sprite);
    double scale = 1 + (rand() % 50) / (float)100;
    sprite->SetScaleX(Vec2(scale, scale));
    Update(0);

    associated.AddComponent(new Collider(associated));
}

void Minion::Update(float dt) {
    arc += rotSpeed * dt;
    associated.angleDeg = 90 + arc * 180 * M_1_PI;

    if (auto alien = alienCenter.lock())
        associated.box.SetCenter(alien->box.Center() +
                                 Vec2(minionDist, 0).RotateRad(arc));
    else
        associated.RequestDelete();
}

void Minion::Shoot(Vec2 target) {
    State* state = Game::GetInstance()->GetState();
    GameObject* gm = new GameObject();
    state->AddObject(gm);

    gm->box.pos = associated.box.Center();
    Vec2 move = target - gm->box.pos;
    gm->AddComponent(new Bullet(*gm, move.AngleDeg(), bulletSpeed, damage,
                                maxDistance, "assets/img/minionbullet2.png", 3,
                                0.1));
}

void Minion::NotifyCollision(std::shared_ptr<GameObject> other) {
    if (associated.fromPlayer == other->fromPlayer) return;
    std::cout << "Collision Minion" << std::endl;

    if (auto bullet = other->GetComponent<Bullet*>())
        if (auto ap = alienCenter.lock())
            if (auto alien = ap->GetComponent<Alien*>())
                alien->TakeDamage(bullet->GetDamage());
}
