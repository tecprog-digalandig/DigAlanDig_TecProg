#include "Alien.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include "Minion.h"
#include "Sprite.h"
#include "State.h"

Alien::Alien(GameObject& associated, int nMinions)
    : Component(associated),
      minionArray(nMinions),
      input(InputManager::GetInstance()) {
    associated.AddComponent(new Collider(associated));
    associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien() {
    for (auto& minion : minionArray) {
        if (auto m = minion.lock()) m->RequestDelete();
    }
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
    int x = input.GetWorldMouseX();
    int y = input.GetWorldMouseY();
    if (input.MousePress(input.mouseKey::RIGHT))
        taskQueue.emplace(Action(Action::SHOOT, x, y));
    if (input.MousePress(input.mouseKey::MIDDLE))
        taskQueue.emplace(Action(Action::MOVE, x, y));

    if (!taskQueue.empty()) {
        Action task = taskQueue.front();
        if (task.type == Action::MOVE) {
            Vec2 center = associated.box.Center();

            Vec2 move = task.pos - center;
            speed = move.Normal() * maxSpeed;
            move = speed * dt;
            associated.box.pos += move;

            if (move.Length() >= Vec2(task.pos - center).Length()) {
                taskQueue.pop();
                speed.Set();
                associated.box.SetCenter(task.pos);
            }
        } else if (task.type == Action::SHOOT) {
            if (std::shared_ptr<GameObject> minionGm = closestMinion(task.pos))
                if (Minion* minion = (Minion*)minionGm->GetComponent("Minion"))
                    minion->Shoot(task.pos);

            taskQueue.pop();
        }
    }

    associated.angleDeg -= degPerS * dt;
    if (hp <= 0) associated.RequestDelete();
}

void Alien::NotifyCollision(std::shared_ptr<GameObject> other) {
    if (associated.fromPlayer == other->fromPlayer) return;

    std::cout << "Collision Alien" << std::endl;
    if (auto bullet = (Bullet*)other->GetComponent("Bullet"))
        TakeDamage(bullet->GetDamage());
}
