#include "Sound.h"
#include <iostream>

void Sound::Play(int times) {
    times -= (times > 0) ? 1 : times;

    if (chunk) {
        if ((channel = Mix_PlayChannel(-1, chunk, times - 1)) == -1)
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
    }
}

void Sound::Stop() {
    if (chunk) Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
    if (chunk) Mix_FreeChunk(chunk);

    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        std::cerr << "Mix_LoadWAV :" << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
}

Sound::~Sound() {
    if (chunk) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}
