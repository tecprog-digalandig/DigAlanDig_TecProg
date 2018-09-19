#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "Camera.h"
#include "Common.h"

Game* Game::_instance = nullptr;

Game::~Game()
{
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete stored_state;
    delete grid_control;
}

Game* Game::getInstance(const std::string& title, int w, int h)
{
    if (!_instance) _instance = new Game(title, w, h);
    return _instance;
}

void Game::updateBeatTime(int time_rhythm)
{
    std::cout << tick_counter << " ; " << time_rhythm << std::endl;
    tick_counter = (tick_counter * 9 + time_rhythm) / 10;
    if (std::abs(tick_counter - time_rhythm) > 1000) tick_counter = time_rhythm;
}

void Game::calculateDeltaTime()
{
    int ticks_total = static_cast<int>(SDL_GetTicks());
    dt = ticks_total - frame_start;
    // Maximum time, fix return from suspended
    if (dt > 1000) dt = 1000;

    tick_counter += dt;
    dt /= 1000;
    frame_start = ticks_total;

    if (input.KeyPress(SDL_SCANCODE_EQUALS))
    {
        adjust += 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }

    if (input.KeyPress(SDL_SCANCODE_MINUS))
    {
        adjust -= 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }

    int fixed_ticks = tick_counter + adjust;
    int new_half_beat_time = fixed_ticks / half_beat_time;

    if (new_half_beat_time > half_beat_counter)
    {
        half_beat_counter = new_half_beat_time;
        should_rhythm_update = true;
        off_beat = half_beat_counter % 2;

    }
    else
    {
        should_rhythm_update = false;
    }

    int a = fixed_ticks - (half_beat_counter / 2) * beat_time;
    int b = fixed_ticks - ((half_beat_counter / 2) + 1) * beat_time;

    int delta_rhythm_ms = (a < -b) ? a : b;
    delta_rhythm = delta_rhythm_ms / (beat_time / 2.0);
}

void Game::run()
{
    if (stored_state)
    {
        stateStack.emplace(stored_state);
        stateStack.top()->start();
        stored_state = nullptr;
    }

    int fpb = 0;
    while (!stateStack.empty())
    {
        calculateDeltaTime();
        input.update(delta_rhythm);

        ++fpb;
        if (should_rhythm_update)
        {
            should_rhythm_update = false;
            if (!off_beat)
            {
                stateStack.top()->rhythmUpdate();
                Camera::rhythmUpdate();
            }
            else
            {
                stateStack.top()->rhythmReset();
                std::cout << "." << off_beat << "." << fpb << std::endl;
                fpb = 0;
            }
        }

        stateStack.top()->update(dt);
        stateStack.top()->render();
        SDL_RenderPresent(renderer);

        if (stateStack.top()->PopRequested() ||
            stateStack.top()->QuitRequested())
        {
            Camera::Follow(nullptr);
            Game::getInstance()->getGridControl()->ClearEnemyVector();
            stateStack.pop();
            Resources::ClearAll();
            if (!stateStack.empty()) stateStack.top()->Resume();
        }

        if (stored_state)
        {
            stateStack.top()->StopMusic();
            stateStack.emplace(stored_state);
            stateStack.top()->start();
            stored_state = nullptr;
            tick_counter = 0;
        }
        SDL_Delay(10);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (input.ActionPress(InputManager::FULLSCREEN))
        {
            toggleFullScreen();
        }
    }
}

void Game::toggleFullScreen()
{
    static bool fullscreen = true;
    unsigned flag = (fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    fullscreen = !fullscreen;

    SDL_SetWindowFullscreen(window, flag);
}

Game::Game(const std::string& title, int width, int height)
    : input(InputManager::getInstance())
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                 SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER |
                 SDL_INIT_HAPTIC) < 0)
                 {
                     std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
                     exit(EXIT_SUCCESS);
                 }

    int init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(init_flags) != init_flags)
    {
        std::cerr << "IMG_Init: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (Mix_OpenAudio(bit_rate, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    init_flags = MIX_INIT_OGG;

    if (Mix_Init(init_flags) != init_flags)
    {
        std::cerr << "Mix_Init: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int nchannels = 32;
    if (Mix_AllocateChannels(nchannels) != nchannels)
    {
        std::cerr << "Mix_AllocateChannels: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }
    Camera::screenSize.Set(width, height);

    SDL_Surface* icon = IMG_Load("assets/icon/icon128.png");
    if (icon)
    {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_TARGETTEXTURE);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);

    grid_control = GridControl::getInstance();
}
