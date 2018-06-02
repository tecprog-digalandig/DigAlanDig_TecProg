#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "Camera.h"

Game* Game::_instance = nullptr;

Game::~Game() {
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete storedState;
}

Game* Game::GetInstance(const std::string& title, int w, int h) {
    if (!_instance) _instance = new Game(title, w, h);
    return _instance;
}

void Game::CalculateDeltaTime() {
    int ticks = static_cast<int>(SDL_GetTicks());
    dt = ticks - frameStart;
    dt /= 1000;
    frameStart = ticks;

    if (input.KeyPress(SDL_SCANCODE_EQUALS)) {
        adjust += 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }
    if (input.KeyPress(SDL_SCANCODE_MINUS)) {
        adjust -= 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }
    if (input.KeyPress(SDL_SCANCODE_0)) {
        keyAdjust += 10;
        std::cout << "Key Adjust = " << keyAdjust << "ms\n";
    }
    if (input.KeyPress(SDL_SCANCODE_9)) {
        keyAdjust -= 10;
        std::cout << "Key Adjust = " << keyAdjust << "ms\n";
    }

    int fixedTicks = ticks + adjust;
    int newHalfBeatCounter = fixedTicks / halfBeatTime;
    if (newHalfBeatCounter > halfBeatCounter) {
        halfBeatCounter = newHalfBeatCounter;
        shouldRhythmUpdate = true;
        offBeat = halfBeatCounter % 2;

    } else {
        shouldRhythmUpdate = false;
    }

    fixedTicks += keyAdjust;
    int a = fixedTicks - (halfBeatCounter / 2) * beatTime;
    int b = ((halfBeatCounter / 2) + 1) * beatTime - fixedTicks;
    int deltaRhythmMs = std::min(a, b);
    deltaRhythm = deltaRhythmMs / (beatTime / 2.0);
}

void Game::Run() {
    if (storedState) {
        stateStack.emplace(storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }

    while (!stateStack.empty()) {
        CalculateDeltaTime();
        input.Update(deltaRhythm);
        stateStack.top()->Update(dt);
        if (shouldRhythmUpdate) {
            if (!offBeat)
                stateStack.top()->RhythmUpdate();
            else
                stateStack.top()->RhythmReset();
            std::cout << "." << offBeat << "." << std::endl;
        }

        stateStack.top()->Render();
        SDL_RenderPresent(renderer);

        if (stateStack.top()->PopRequested() ||
            stateStack.top()->QuitRequested()) {
            stateStack.pop();
            Resources::ClearAll();
            if (!stateStack.empty()) stateStack.top()->Resume();
        }

        if (storedState) {
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        SDL_Delay(10);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
}

/* Private */
Game::Game(const std::string& title, int width, int height)
    : input(InputManager::GetInstance()) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(init_flags) != init_flags) {
        std::cerr << "IMG_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
    init_flags = MIX_INIT_OGG;
    if (Mix_Init(init_flags) != init_flags) {
        std::cerr << "Mix_Init: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int nchannels = 32;
    if (Mix_AllocateChannels(nchannels) != nchannels) {
        std::cerr << "Mix_AllocateChannels: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (TTF_Init()) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
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
}
