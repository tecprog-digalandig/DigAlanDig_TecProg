#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
    Resources::image_table;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>>
    Resources::music_table;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>
    Resources::sound_table;

<<<<<<< HEAD
std::shared_ptr<SDL_Texture> Resources::getImage(const std::string& file) {
    auto got = image_table.find(file);

    if (got == image_table.end()) {
        SDL_Texture* tex =
            IMG_LoadTexture(Game::getInstance()->GetRenderer(), file.c_str());
        if (!tex) {
=======
std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file)
{
    auto got = imageTable.find(file);

    if (got == imageTable.end()) 
    {
        SDL_Texture* tex =
            IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
        if (!tex)
        {
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
            std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }

        std::shared_ptr<SDL_Texture> sp(
            tex, [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); });
        image_table.emplace(file, sp);
    }

    return image_table[file];
}

<<<<<<< HEAD
void Resources::clearImages() {
    for (auto element : image_table)
        if (element.second.unique()) image_table.erase(element.first);
=======
void Resources::ClearImages() 
{
    for (auto element : imageTable)
        if (element.second.unique()) imageTable.erase(element.first);
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
}

std::shared_ptr<Mix_Music> Resources::getMusic(const std::string& file) {
    auto got = music_table.find(file);

<<<<<<< HEAD
    if (got == music_table.end()) {
=======
    if (got == musicTable.end()) 
    {
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
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

<<<<<<< HEAD
void Resources::clearMusics() {
    for (auto element : music_table)
        if (element.second.unique()) music_table.erase(element.first);
}

std::shared_ptr<Mix_Chunk> Resources::getSound(const std::string& file) {
    auto got = sound_table.find(file);

    if (got == sound_table.end()) {
=======
void Resources::ClearMusics()
{
    for (auto element : musicTable)
        if (element.second.unique()) musicTable.erase(element.first);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file)
{
    auto got = soundTable.find(file);

    if (got == soundTable.end())
    {
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
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

<<<<<<< HEAD
void Resources::clearSounds() {
    for (auto element : sound_table)
        if (element.second.unique()) sound_table.erase(element.first);
}

void Resources::clearAll() {
    clearImages();
    clearMusics();
    clearSounds();
=======
void Resources::ClearSounds()
{
    for (auto element : soundTable)
        if (element.second.unique()) soundTable.erase(element.first);
}

void Resources::ClearAll()
{
    ClearImages();
    ClearMusics();
    ClearSounds();
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
}
