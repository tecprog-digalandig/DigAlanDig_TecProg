#include "Minion.h"
#include "Bullet.h"
#include "Game.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg)
    : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg) {
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent((Component*)sprite);

    double scale = 1 + (rand() % 50) / (float)100;
    std::cout << std::endl << scale << std::endl;
    sprite->SetScaleX(Vec2(scale, scale));
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
    State* state = Game::getInstance()->getState();
    GameObject* gm = new GameObject();
    state->AddObject(gm);

    gm->box.pos = associated.box.Center();
    Vec2 move = target - gm->box.pos;
    gm->AddComponent(new Bullet(*gm, move.Angle(), bulletSpeed, damage,
                                maxDistance, "assets/img/minionbullet2.png", 3,
                                0.1));
}
