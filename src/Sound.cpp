#include "Sound.h"
#include <iostream>
#include <assert.h>

void Sound::play_func(int times) 
{   
    assert(times > 0);
    times -= (times > 0) ? 1 : times;

    if (chunk) {
        //if ((channel = mixPlayChannel(-1, chunk.get(), times)) == -1)
            //std::cerr << "Mix_PlayChannel: " << mixGetError() << std::endl;
    }
    assert(played == true);
    played = true;
}
