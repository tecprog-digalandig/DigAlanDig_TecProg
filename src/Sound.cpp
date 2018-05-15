#include "Sound.h"
#include <iostream>

void Sound::Play(int times) {
    times -= (times > 0) ? 1 : times;

    if (chunk) {
        if ((channel = Mix_PlayChannel(-1, chunk.get(), times)) == -1)
            std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
    }
    played = true;
}
