#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
    Resources::image_table;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
    Resources::music_table;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
    Resources::sound_table;

std::shared_ptr<SDL_Texture> Resources::getImage(const std::string& file) {
    auto got = image_table.find(file);

    if (got == image_table.end()) {
        SDL_Texture* tex =
            IMG_LoadTexture(Game::getInstance()->GetRenderer(), file.c_str());
        if (!tex) {
            std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<SDL_Texture> sp(
            tex, [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); });
        image_table.emplace(file, sp);
    }

    return image_table[file];
}

void Resources::clearImages() {
    for (auto element : image_table)
        if (element.second.unique()) image_table.erase(element.first);
}

std::shared_ptr<Mix_Music> Resources::getMusic(const std::string& file) {
    auto got = music_table.find(file);

    if (got == music_table.end()) {
        Mix_Music* mus = Mix_LoadMUS(file.c_str());
        if (!mus) {
            std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<Mix_Music> sp(
            mus, [](Mix_Music* ptr) { Mix_FreeMusic(ptr); });
        music_table.emplace(file, sp);
    }

    return music_table[file];
}

void Resources::clearMusics() {
    for (auto element : music_table)
        if (element.second.unique()) music_table.erase(element.first);
}

std::shared_ptr<Mix_Chunk> Resources::getSound(const std::string& file) {
    auto got = sound_table.find(file);

    if (got == sound_table.end()) {
        Mix_Chunk* snd = Mix_LoadWAV(file.c_str());
        if (!snd)
        {
            std::cerr << "Mix_LoadWAV: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        std::shared_ptr<Mix_Chunk> sp(
            snd, [](Mix_Chunk* ptr) { Mix_FreeChunk(ptr); });
        sound_table.emplace(file, sp);
    }

    return sound_table[file];
}

void Resources::clearSounds() {
    for (auto element : sound_table)
        if (element.second.unique()) sound_table.erase(element.first);
}

void Resources::clearAll() {
    clearImages();
    clearMusics();
    clearSounds();
}
