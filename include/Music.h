#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

class Music {
  public:
    Music(void);
    Music(std::string file);
    ~Music(void);
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen(void);

  private:
    Mix_Music* music = nullptr;
};
