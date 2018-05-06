#include "Alien.h"
#include "Sprite.h"

Alien::Alien(GameObject& associated, int nMinions)
    : Component(associated),
      speed(),
      minionArray(nMinions),
      input(InputManager::GetInstance()) {
    associated.AddComponent(
        (Component*)new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien() {
    /*for (auto& minion : minionArray) {
        delete minion;
    }*/
    // TODO delete weak_prt?
}

void Alien::Start() {
    for (unsigned int i = 0; i < minionArray.size(); ++i) {
        // TODO
    }
}

void Alien::Update(float dt) {
    int x = input.GetWorldMouseX();
    int y = input.GetWorldMouseY();
    if (input.IsMouseDown(input.mouseKey::RIGHT))
        taskQueue.emplace(Action(Action::SHOOT, x, y));
    if (input.MousePress(input.mouseKey::MIDDLE))
        taskQueue.emplace(Action(Action::MOVE, x, y));
    if (input.IsMouseDown(input.mouseKey::LEFT))
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
                speed.Set(0, 0);
                associated.box.SetCenter(task.pos);
            }
        } else {
            // TODO
            taskQueue.pop();
        }
    }

    if (hp <= 0) associated.RequestDelete();
}
