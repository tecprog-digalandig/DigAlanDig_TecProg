#include "Face.h"
#include "Sound.h"

#include <iostream>
#include <string>
#include <typeinfo>

void Face::Damage(int damage) {
    if (hitpoints -= damage > 0) return;

    if (Sound* sound = (Sound *) associated.GetComponent("Sound")) sound->Play();

    associated.RequestDelete();
}

bool Face::Is(std::string type) {
    std::cout << type << std::endl;
    std::cout << typeid(*this).name() << std::endl;
    return !type.compare(typeid(*this).name());
}
