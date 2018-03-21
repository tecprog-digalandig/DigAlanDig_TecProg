#include "Music.h"

Music::Music(void):
    music(nullptr)
{
}

Music::Music(std::string file):
    music(nullptr)
{
    Open(file);
}

Music::~Music(void)
{
    Mix_FreeMusic(music);
}

void Music::Play(int times)
{
    if(IsOpen())
    {
        if(Mix_PlayMusic(music, times) == -1)
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;

    }
}

void Music::Stop(int msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file)
{
    if(IsOpen())
        Mix_FreeMusic(music);

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr)
    {
        std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
}


bool Music::IsOpen(void)
{
    if (Music::music)
        return true;
    return false;
}
