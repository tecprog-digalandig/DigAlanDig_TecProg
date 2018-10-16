#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<sdl_texture>>
    Resources::image_table;
std::unordered_map<std::string, std::shared_ptr<mix_music>>
    Resources::music_table;
std::unordered_map<std::string, std::shared_ptr<mix_chunk>>
    Resources::sound_table;

std::shared_ptr<sdl_texture> Resources::GetImage(const std::string& file) {
    auto got = image_table.find(file);

    if (got == image_table.end()) {
        sdl_texture* tex =
            IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
        if (!tex) {
            std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<sdl_texture> sp(
            tex, [](sdl_texture* ptr) { SDL_DestroyTexture(ptr); });
        image_table.emplace(file, sp);
    }

    return image_table[file];
}

void Resources::ClearImages() {
    for (auto element : image_table)
        if (element.second.unique()) image_table.erase(element.first);
}

std::shared_ptr<mix_music> Resources::GetMusic(const std::string& file) {
    auto got = musicTable.find(file);

    if (got == musicTable.end()) {
        mix_music* mus = Mix_LoadMUS(file.c_str());
        if (!mus) {
            std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<mix_music> sp(
            mus, [](mix_music* ptr) { Mix_FreeMusic(ptr); });
        musicTable.emplace(file, sp);
    }

    return musicTable[file];
}

void Resources::ClearMusics() {
    for (auto element : musicTable)
        if (element.second.unique()) musicTable.erase(element.first);
}

std::shared_ptr<mix_chunk> Resources::GetSound(const std::string& file) {
    auto got = sound_table.find(file);

    if (got == sound_table.end()) {
        mix_chunk* snd = Mix_LoadWAV(file.c_str());
        if (!snd) {
            std::cerr << "Mix_LoadWAV: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        std::shared_ptr<mix_chunk> sp(
            snd, [](mix_chunk* ptr) { Mix_FreeChunk(ptr); });
        sound_table.emplace(file, sp);
    }

    return sound_table[file];
}

void Resources::ClearSounds() {
    for (auto element : sound_table)
        if (element.second.unique()) sound_table.erase(element.first);
}

void Resources::ClearAll() {
    ClearImages();
    ClearMusics();
    ClearSounds();
}
