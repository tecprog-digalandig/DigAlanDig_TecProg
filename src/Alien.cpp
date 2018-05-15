#include "Alien.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include "Minion.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions)
    : Component(associated),
      minionArray(nMinions),
      input(InputManager::GetInstance()) {
    associated.AddComponent(new Collider(associated));
    associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
    alienCount++;
}

Alien::~Alien() {
    for (auto& minion : minionArray) {
        if (auto m = minion.lock()) m->RequestDelete();
    }
    alienCount--;
}

void Alien::Start() {
    int i = 0;
    State* state = Game::GetInstance()->GetState();

    for (auto& minion : minionArray) {
        if (minion.expired()) {
            GameObject* gm = new GameObject();
            minion = state->AddObject(gm);
            gm->AddComponent(new Minion(*gm, state->GetObjectPrt(&associated),
                                        (2 * M_PI * i++) / minionArray.size()));
        }
    }
}
std::shared_ptr<GameObject> Alien::closestMinion(const Vec2& target) {
    float minDist = 1e9;
    std::shared_ptr<GameObject> ret;

    for (auto& minion : minionArray) {
        if (std::shared_ptr<GameObject> m = minion.lock()) {
            float dist = Vec2(target - m->box.Center()).Length();
            if (dist <= minDist) {
                ret = m;
                minDist = dist;
            }
        }
    }

    return ret;
}

void Alien::Update(float dt) {
    switch (state) {
        case MOVING: {
            Vec2 center = associated.box.Center();

            Vec2 move = destination - center;
            speed = move.Normal() * maxSpeed;
            move = speed * dt;
            associated.box.pos += move;

            if (move.Length() >= Vec2(destination - center).Length()) {
                state = AlienState::RESTING;
                restTimer.Restart();
                speed.Set();
                associated.box.SetCenter(destination);
                destination = Camera::Center();
                if (std::shared_ptr<GameObject> minionGm =
                        closestMinion(destination))
                    if (auto minion = minionGm->GetComponent<Minion*>())
                        minion->Shoot(destination);
            }

            break;
        }
        case RESTING:
            restTimer.Update(dt);
            if (restTimer.Get() > restDuration) {
                state = AlienState::MOVING;
                destination = Camera::Center();
            }
            break;
    }
    associated.angleDeg -= degPerS * dt;

    if (hp <= 0) {
        associated.RequestDelete();
        GameObject* gm = new GameObject();
        gm->CopyPosition(associated);
        gm->AddComponent(
            new Sprite(*gm, "assets/img/aliendeath.png", 4, 0.4, 1.6));
        gm->AddComponent(new Sound(*gm, "assets/audio/boom.wav", true));
        gm->Start();
        Game::GetInstance()->GetState()->AddObject(gm);
    }
}

void Alien::NotifyCollision(std::shared_ptr<GameObject> other) {
    if (associated.fromPlayer == other->fromPlayer) return;

    std::cout << "Collision Alien" << std::endl;
    if (auto bullet = other->GetComponent<Bullet*>())
        TakeDamage(bullet->GetDamage());
}
