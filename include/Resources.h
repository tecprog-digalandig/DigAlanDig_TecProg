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
    static std::shared_ptr<SDL_Texture> getImage(const std::string& file);
    static void clearImages();

    static std::shared_ptr<Mix_Music> getMusic(const std::string& file);
    static void clearMusics();

    static std::shared_ptr<Mix_Chunk> getSound(const std::string& file);
    static void clearSounds();

    static void clearAll();

  private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
        image_table;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
        music_table;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
        sound_table;
};

#endif  // RESOURCES_H
