#include "Face.h"
#include <iostream>
#include "InputManager.h"
#include "Sound.h"

void Face::Damage(int damage) {
    if ((hitpoints -= damage) > 0) return;

    if (Sound* sound = dynamic_cast<Sound*>(associated.GetComponent("Sound")))
        sound->Play();

    associated.RequestDelete();
}

void Face::Update(float dt) {
    if (InputManager::GetInstance().MousePress(1) &&
        associated.box.IsInside(
            (double)InputManager::GetInstance().GetWorldMouseX(),
            (double)InputManager::GetInstance().GetWorldMouseY())) {
        Damage(std::rand() % 10 + 10);
    }
}
