#ifndef MUSIC_H
#define MUSIC_H
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "Resources.h"
#include "SDL_include.h"

#include <iostream>
#include <string>

class Music {
  public:
    Music(void) : music(nullptr) {}
    Music(const std::string &file) : music(nullptr) { Open(file); }
    ~Music(void) {}

    void Play(int times = -1) const;
    void Stop(int msToStop = 1500) const { Mix_FadeOutMusic(msToStop); }
    void Open(const std::string &file) { music = Resources::GetMusic(file); }

    bool IsOpen(void) const { return (bool)music; }

  private:
    Mix_Music *music = nullptr;
};

#endif
