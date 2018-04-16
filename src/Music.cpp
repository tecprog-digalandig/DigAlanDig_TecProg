#include "Music.h"

void Music::Play(int times) const {
    if (music) {
        if (Mix_PlayMusic(music, times) == -1)
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
    }
}
