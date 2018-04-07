#include "Face.h"
#include "Sound.h"

void Face::Damage(int damage) {
    if ((hitpoints -= damage) > 0) return;

    if (Sound* sound = (Sound*)associated.GetComponent("Sound")) sound->Play();

    associated.RequestDelete();
}
