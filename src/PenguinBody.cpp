#include "PenguinBody.h"
#include "Game.h"
#include "Sprite.h"

PenguinBody::PenguinBody(GameObject& associated)
    : Component(associated), player(this), input(InputManager::GetInstance()) {
    associated.AddComponent(
        (Component*)new Sprite(associated, "assets/img/penguin.png"));
}

void PenguinBody::Start() {
    State* state = Game::getInstance()->getState();

    GameObject* gm = new GameObject();
    pcannon = state->AddObject(gm);
    gm->AddComponent(new PenguinCannon(*gm, state->GetObjectPrt(&associated)));
}

inline int inRange(float value, float min, float max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

void PenguinBody::Update(float dt) {
    if (input.IsKeyDown(SDL_SCANCODE_W)) linearSpeed += accel * dt;
    if (input.IsKeyDown(SDL_SCANCODE_S)) linearSpeed -= accel * dt;
    if (input.IsKeyDown(SDL_SCANCODE_D)) angle += rotSpeed * dt;
    if (input.IsKeyDown(SDL_SCANCODE_A)) angle -= rotSpeed * dt;

    associated.angleDeg = angle;
    linearSpeed *= 1 - drag * dt;
    linearSpeed = inRange(linearSpeed, minSpeed, maxSpeed);

    speed = Vec2(linearSpeed, 0).Rotate(angle);
    associated.box.pos += speed * dt;

    if (hp <= 0) {
        if (auto p = pcannon.lock()) p->RequestDelete();
        associated.RequestDelete();
    }
}
