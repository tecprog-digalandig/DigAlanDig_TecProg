#include "Sound.h"
#include <iostream>

void Sound::play(int times) 
{
    times -= (times > 0) ? 1 : times;

    if (chunk) {
        if ((channel = mixPlayChannel(-1, chunk.get(), times)) == -1)
            std::cerr << "Mix_PlayChannel: " << mixGetError() << std::endl;
    }
    played = true;
}
