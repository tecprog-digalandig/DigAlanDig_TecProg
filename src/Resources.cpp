#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
    Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
    Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
    Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file) {
    auto got = imageTable.find(file);

    if (got == imageTable.end()) {
        SDL_Texture* tex =
            IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
        if (!tex) {
            std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<SDL_Texture> sp(
            tex, [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); });
        imageTable.emplace(file, sp);
    }

    return imageTable[file];
}

void Resources::ClearImages() {
    for (auto element : imageTable)
        if (element.second.unique()) imageTable.erase(element.first);
}

std::shared_ptr<Mix_Music> Resources::GetMusic(const std::string& file) {
    auto got = musicTable.find(file);

    if (got == musicTable.end()) {
        Mix_Music* mus = Mix_LoadMUS(file.c_str());
        if (!mus) {
            std::cerr << "Mix_LoadMUS :" << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<Mix_Music> sp(
            mus, [](Mix_Music* ptr) { Mix_FreeMusic(ptr); });
        musicTable.emplace(file, sp);
    }

    return musicTable[file];
}

void Resources::ClearMusics() {
    for (auto element : musicTable)
        if (element.second.unique()) musicTable.erase(element.first);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file) {
    auto got = soundTable.find(file);

    if (got == soundTable.end()) {
        Mix_Chunk* snd = Mix_LoadWAV(file.c_str());
        if (!snd) {
            std::cerr << "Mix_LoadWAV: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        std::shared_ptr<Mix_Chunk> sp(
            snd, [](Mix_Chunk* ptr) { Mix_FreeChunk(ptr); });
        soundTable.emplace(file, sp);
    }

    return soundTable[file];
}

void Resources::ClearSounds() {
    for (auto element : soundTable)
        if (element.second.unique()) soundTable.erase(element.first);
}

std::shared_ptr<TTF_Font> Resources::GetFont(const std::string& file,
                                             int ptsize) {
    std::string key = file + std::to_string(ptsize);
    auto got = fontTable.find(key);

    if (got == fontTable.end()) {
        TTF_Font* font = TTF_OpenFont(file.c_str(), ptsize);
        if (!font) {
            std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        std::shared_ptr<TTF_Font> sp(font,
                                     [](TTF_Font* ptr) { TTF_CloseFont(ptr); });
        fontTable.emplace(file, sp);
    }

    return fontTable[file];
}

void Resources::ClearFonts() {
    for (auto element : fontTable)
        if (element.second.unique()) fontTable.erase(element.first);
}

void Resources::ClearAll() {
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}
