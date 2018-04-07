#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

class Music {
  public:
    Music(void) : music(nullptr) {}
    Music(std::string file) : music(nullptr) { Open(file); }
    ~Music(void) {
        if (music) Mix_FreeMusic(music);
    }

    void Play(int times = -1);
    void Stop(int msToStop = 1500) { Mix_FadeOutMusic(msToStop); }
    void Open(std::string file);
    bool IsOpen(void) { return (bool)(music); }

  private:
    Mix_Music* music = nullptr;
};
