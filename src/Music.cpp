/**
* @file Music.cpp
* @copyright 2018 Pedro H.
* @brief Class responsible for playing the game song for each state of the game.
*/

#include "Music.h"

/**
* @brief Control if the music is played
* @param [in] times
* @return void
* @details Music is set off if times = -1
*/
void Music::Play(int times) const
{
    if (music)
    {
        if (Mix_PlayMusic(music.get(), times) == -1)
        {
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
        }
    }
}
