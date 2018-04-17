#include "Face.h"
#include "InputManager.h"
#include "Sound.h"

void Face::Damage(int damage) {
    if ((hitpoints -= damage) > 0) return;

    if (Sound* sound = (Sound*)associated.GetComponent("Sound")) sound->Play();

    associated.RequestDelete();
}

void Face::Update(float dt) {
    if (InputManager::GetInstance().MousePress(1) &&
        associated.box.IsInside(
            (double)InputManager::GetInstance().GetMouseX(),
            (double)InputManager::GetInstance().GetMouseY())) {
        Damage(std::rand() % 10 + 10);
    }
}
