#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "Camera.h"
#include "Common.h"

Game* Game::_instance = nullptr;

Game::~Game() {
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete storedState;
    delete gridControl;
}

Game* Game::GetInstance(const std::string& title, int w, int h) {
    if (!_instance) _instance = new Game(title, w, h);
    return _instance;
}

void Game::UpdateBeatTime(int timeRhythm) {
    std::cout << tickCounter << " ; " << timeRhythm << std::endl;
    tickCounter = (tickCounter * 9 + timeRhythm) / 10;
    if (std::abs(tickCounter - timeRhythm) > 1000) tickCounter = timeRhythm;
}

void Game::CalculateDeltaTime() {
    int ticksTotal = static_cast<int>(SDL_GetTicks());
    dt = ticksTotal - frameStart;
    // Maximum time, fix return from suspended
    if (dt > 1000) dt = 1000;

    tickCounter += dt;
    dt /= 1000;
    frameStart = ticksTotal;

    if (input.KeyPress(SDL_SCANCODE_EQUALS)) {
        adjust += 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }
    if (input.KeyPress(SDL_SCANCODE_MINUS)) {
        adjust -= 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }

    int fixedTicks = tickCounter + adjust;
    int newHalfBeatCounter = fixedTicks / halfBeatTime;
    if (newHalfBeatCounter > halfBeatCounter) {
        halfBeatCounter = newHalfBeatCounter;
        shouldRhythmUpdate = true;
        offBeat = halfBeatCounter % 2;

    } else {
        shouldRhythmUpdate = false;
    }

    int a = fixedTicks - (halfBeatCounter / 2) * beatTime;
    int b = fixedTicks - ((halfBeatCounter / 2) + 1) * beatTime;

    int deltaRhythmMs = (a < -b) ? a : b;
    deltaRhythm = deltaRhythmMs / (beatTime / 2.0);
}

void Game::Run() {
    if (storedState) {
        stateStack.emplace(storedState);
        stateStack.top()->start();
        storedState = nullptr;
    }

    int fpb = 0;
    while (!stateStack.empty()) {
        CalculateDeltaTime();
        input.update(deltaRhythm);

        fpb++;
        if (shouldRhythmUpdate) {
            shouldRhythmUpdate = false;
            if (!offBeat) {
                stateStack.top()->rhythmUpdate();
                Camera::rhythmUpdate();
            } else
                stateStack.top()->RhythmReset();
            std::cout << "." << offBeat << "." << fpb << std::endl;
            fpb = 0;
        }

        stateStack.top()->update(dt);
        stateStack.top()->render();
        SDL_RenderPresent(renderer);

        if (stateStack.top()->PopRequested() ||
            stateStack.top()->QuitRequested()) {
            Camera::Follow(nullptr);
            Game::GetInstance()->GetGridControl()->ClearEnemyVector();
            stateStack.pop();
            Resources::ClearAll();
            if (!stateStack.empty()) stateStack.top()->Resume();
        }

        if (storedState) {
            stateStack.top()->StopMusic();
            stateStack.emplace(storedState);
            stateStack.top()->start();
            storedState = nullptr;
            tickCounter = 0;
        }
        SDL_Delay(10);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (input.ActionPress(InputManager::FULLSCREEN)) ToggleFullScreen();
    }
}

void Game::ToggleFullScreen() {
    static bool fullscreen = true;
    unsigned flag = (fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    fullscreen = !fullscreen;

    SDL_SetWindowFullscreen(window, flag);
}

Game::Game(const std::string& title, int width, int height)
    : input(InputManager::GetInstance()) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                 SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER |
                 SDL_INIT_HAPTIC) < 0) {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(init_flags) != init_flags) {
        std::cerr << "IMG_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (Mix_OpenAudio(bitRate, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
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

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
    Camera::screenSize.Set(width, height);

    SDL_Surface* icon = IMG_Load("assets/icon/icon128.png");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);

    gridControl = GridControl::GetInstance();
}
