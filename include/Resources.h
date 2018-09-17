#ifndef RESOURCES_H
#define RESOURCES_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <memory>
#include <string>
#include <unordered_map>

class Resources 
{
  public:
    static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);
    static void ClearImages();

    static std::shared_ptr<Mix_Music> GetMusic(const std::string& file);
    static void ClearMusics();

    static std::shared_ptr<Mix_Chunk> GetSound(const std::string& file);
    static void ClearSounds();

    static void ClearAll();

  private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
        imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
        musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
        soundTable;
};

#endif  // RESOURCES_H
