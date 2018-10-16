#ifndef RESOURCES_H
#define RESOURCES_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Music.h"

#include <memory>
#include <string>
#include <unordered_map>

class Resources 
{
  public:
    static std::shared_ptr<sdl_texture> getImage(const std::string& file);
    static void clearImages();

    static std::shared_ptr<mix_music> getMusic(const std::string& file);
    static void clearMusics();

    static std::shared_ptr<mix_chunk> getSound(const std::string& file);
    static void clearSounds();

    static void clearAll();

  private:

    
    static std::unordered_map<std::string, std::shared_ptr<sdl_texture>>
        image_table;
    static std::unordered_map<std::string, std::shared_ptr<mix_music>>
        music_table;
    static std::unordered_map<std::string, std::shared_ptr<mix_chunk>>
        sound_table;
};

#endif  // RESOURCES_H
