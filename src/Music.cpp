#include "Music.h"

void Music::Play(int times) {
    if (music) {
        if (Mix_PlayMusic(music, times) == -1)
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
    }
}


void Music::Open(std::string file) {
    if (IsOpen()) Mix_FreeMusic(music);

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
}

