/**
 * @brief 
 * 
 * @file Resources.h
 * 
 */
#ifndef RESOURCES_H
#define RESOURCES_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <memory>
#include <string>
#include <unordered_map>

// Resources Class characteristics and heritages.
class Resources 
// Resource now is going to work with allocations and deallocations.
{
  public:
    // Manage textures.
    // Once the texture is allocated, "get" functions will work as a call instead of a method to load texture.
    static std::shared_ptr<sdl_texture> getImage(const std::string& file);
    static void clearImages();
    // Runs through the image table destroying texture by texture until empty the table.
    
    static std::shared_ptr<mix_music> getMusic(const std::string& file);
    static void clearMusics();
    // Runs through the music table destroying texture by texture until empty the table.

    static std::shared_ptr<mix_chunk> getSound(const std::string& file);
    static void clearSounds();
    // Runs through the sound table destroying texture by texture until empty the table.

    static void clearAll();
    // Clear all the table (Great option to free some game memory during the program).

  private:
    // "shared_ptr" is used to count users from a resource.
    // "unordered_map" is a hash table (template) which receives to parameters.
    // The parameters are a type used as key to the table and content pointed from the key.
    static std::unordered_map<std::string, std::shared_ptr<sdl_texture>>
        image_table;
        // "image_table" is associed a string to a texture pointer.
    static std::unordered_map<std::string, std::shared_ptr<mix_music>>
        music_table;
        // "music_table" is associed a string to a texture pointer.
    static std::unordered_map<std::string, std::shared_ptr<mix_chunk>>
        sound_table;
        // "sound_table" is associed a string to a texture pointer.

    // Everytime is charged a new texture, it's kept in a table so it won't be necessary to load twice.
};

#endif  // RESOURCES_H
