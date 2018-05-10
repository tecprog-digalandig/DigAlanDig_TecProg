#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    auto got = imageTable.find(file);

    if (got == imageTable.end()) {
        SDL_Texture* tex =
            IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
        if (!tex) {
            std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        imageTable[file] = tex;
    }

    return imageTable[file];
}

void Resources::ClearImages() {
    for (auto a : imageTable)
        if (a.second) SDL_DestroyTexture(a.second);
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    auto got = musicTable.find(file);

    if (got == musicTable.end()) {
        Mix_Music* mus = Mix_LoadMUS(file.c_str());
        if (!mus) {
            std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        musicTable[file] = mus;
    }

    return musicTable[file];
}

void Resources::ClearMusics() {
    for (auto a : musicTable)
        if (a.second) Mix_FreeMusic(a.second);
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    auto got = soundTable.find(file);

    if (got == soundTable.end()) {
        Mix_Chunk* snd = Mix_LoadWAV(file.c_str());
        if (!snd) {
            std::cerr << "Mix_LoadWAV :" << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        soundTable[file] = snd;
    }

    return soundTable[file];
}

void Resources::ClearSounds() {
    for (auto a : soundTable)
        if (a.second) Mix_FreeChunk(a.second);
}
