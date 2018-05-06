#include "Game.h"
#include <iostream>
#include <string>
#include "Camera.h"

Game* Game::_instance = nullptr;

Game::~Game(void) {
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete state;
}

Game* Game::getInstance(const std::string& title, int w, int h) {
    if (!_instance) _instance = new Game(title, w, h);
    return _instance;
}

void Game::CalculateDeltaTime() {
    int ticks = SDL_GetTicks();
    dt = ticks - frameStart;
    dt /= 1000;
    frameStart = ticks;
}

void Game::run(void) {
    state = new State();
    state->Start();
    InputManager& input = InputManager::GetInstance();

    while (!state->QuitRequested()) {
        CalculateDeltaTime();
        input.Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }
}

/* Private */
Game::Game(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(init_flags) != init_flags) {
        std::cerr << "IMG_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    init_flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if (Mix_Init(init_flags) != init_flags) {
        std::cerr << "Mix_Init: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int nchannels = 32;
    if (Mix_AllocateChannels(nchannels) != nchannels) {
        std::cerr << "Mix_AllocateChannels: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
    Camera::screenSize.Set(width, height);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    state = nullptr;
}
