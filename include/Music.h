#ifndef MUSIC_H
#define MUSIC_H
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <memory>
#include <string>
#include "Resources.h"

class Music {
  public:
    Music() : music(nullptr) {}
    //explicit Music(const std::string &file) : music(nullptr) { isOpen(file); }
    ~Music() {}

    void play_func(int times = -1) const;
    void stop(int msToStop = 1500) const { Mix_FadeOutMusic(msToStop); }
    //void isOpen(const std::string &file) { music = Resources::getMusic(file); }

    bool isOpen() const { return (bool)music; }

    Mix_Music *getMixMusic() { return music.get(); }

  private:
    std::shared_ptr<Mix_Music> music = nullptr;
};

#endif
