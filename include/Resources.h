#ifndef RESOURCES_H
#define RESOURCES_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <memory>
#include <string>
#include <unordered_map>
#include "SDL_include.h"

class Resources {
  public:
    static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);
    static void ClearImages();

    static std::shared_ptr<Mix_Music> GetMusic(const std::string& file);
    static void ClearMusics();

    static std::shared_ptr<Mix_Chunk> GetSound(const std::string& file);
    static void ClearSounds();

    static std::shared_ptr<TTF_Font> GetFont(const std::string& file,
                                             int ptsize);
    static void ClearFonts();

    static void ClearAll();

  private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
        imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
        musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
        soundTable;
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
};

#endif  // RESOURCES_H
