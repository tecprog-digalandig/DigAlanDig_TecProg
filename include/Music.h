#ifndef MUSIC_H
#define MUSIC_H
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include "Resources.h"

class Music
{
    public:
        Music() : music(nullptr) {}
        explicit Music(const std::string &file) : music(nullptr) { Open(file); }
        ~Music() {}

        void Play(int times = -1) const;
        void Stop(int msToStop = 1500) const { Mix_FadeOutMusic(msToStop); }
        void Open(const std::string &file) { music = Resources::GetMusic(file); }

        bool IsOpen() const { return (bool)music; }

        Mix_Music *GetMixMusic() { return music.get(); }

    private:
        std::shared_ptr<Mix_Music> music = nullptr;
};

#endif
