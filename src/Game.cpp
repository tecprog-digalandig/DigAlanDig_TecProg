/**
* @file Game.cpp
* @copyright 2018 Pedro H.
* @brief Class that starts new game, calculate input time over the movement of
* the caracter on screen (delta time), keep the game running and free resources
* when the game is ended.
*/


#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "Camera.h"
#include "Common.h"
#include <assert.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

Game* Game::_instance = nullptr;

/**
* Make sure to free allocated memory space.
*/
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


/**
* @brief Main game loop
*/
void Game::run()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in Game::run");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Game::run accessed");

        storedStateIsTrue();

        int fpb = 0;
        while (!stateStack.empty())
        {
            calculateDeltaTime();

            input.update(delta_rhythm);

            fpb = fbp + 1;

            runRhythmUpdate();

            stateStack.top()->update(dt);
            stateStack.top()->render();
            SDL_RenderPresent(renderer);

            checkStateRequested();

            storedStateIsTrue();

            SDL_Delay(10);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            if (input.ActionPress(InputManager::FULLSCREEN))
            {
                toggleFullScreen();
            }
            else
            {
                //Nothing to do
            }
        }
    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

Game::Game(const std::string& title, int width, int height)
    : input(InputManager::getInstance())
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in Game constructor");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Game constructor initialized successfully");

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                     SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER |
                     SDL_INIT_HAPTIC) < 0)
         {
             std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
             exit(EXIT_SUCCESS);
         }
         else
         {
             //Nothing to do
         }

        int init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
        if (IMG_Init(init_flags) != init_flags)
        {
            std::cerr << "IMG_Init: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }

        if (Mix_OpenAudio(bit_rate, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        {
            std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }

        init_flags = MIX_INIT_OGG;

        if (Mix_Init(init_flags) != init_flags)
        {
            std::cerr << "Mix_Init: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }

        int nchannels = 32;
        if (Mix_AllocateChannels(nchannels) != nchannels)
        {
            std::cerr << "Mix_AllocateChannels: " << Mix_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, width, height,
                                  SDL_WINDOW_RESIZABLE);
        if (!window)
        {
            std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }
        Camera::screenSize.Set(width, height);

        SDL_Surface* icon = IMG_Load("assets/icon/icon128.png");
        if (icon)
        {
            SDL_SetWindowIcon(window, icon);
            SDL_FreeSurface(icon);
        }
        else
        {
            //Nothing to do
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_TARGETTEXTURE);
        if (!renderer)
        {
            std::cerr << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Nothing to do
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, width, height);

        grid_control = GridControl::getInstance();
    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}


/**
* @brief Starts new game
* @param [in] title, w, h
* @return pointer to class Game
*/

Game* Game::getInstance(const std::string& title, int w, int h)
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in Game::getInstance");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Game::getInstance accessed");

        if (!_instance)
        {
            _instance = new Game(title, w, h);
        }
        else
        {
            //Nothing to do
        }
        assert(_instance != nullptr);
        return _instance;
    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}


/**
* @brief Keep the rhythm of movement in the game
* @param [in] time rhythm is a integer value for measure the game rhythm
* @return void
*/

void Game::updateBeatTime(int time_rhythm)
{
    std::cout << tick_counter << " ; " << time_rhythm << std::endl;
    tick_counter = (tick_counter * 9 + time_rhythm) / 10;
    if (std::abs(tick_counter - time_rhythm) > 1000)
    {
        tick_counter = time_rhythm;
    }
    else
    {
        //Nothing to do
    }
}

/**
* @brief Delta time is the variation of time between human imput and movement of
* the character on the screen.
*/

void Game::calculateDeltaTime()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in Game::calculateDeltaTime");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Game::calculateDeltaTime correctly");

        /**
        *Keeps delta time under 1000 ms,for smoothness in movement
        */
        dt = setDeltaTime(dt);

        assert(dt<=1000);

        tick_counter += dt;
        dt /= 1000;
        frame_start = ticks_total;

        checkInput();

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
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
    int ticks_total = static_cast<int>(SDL_GetTicks());
    dt = ticks_total - frame_start;
}

void Game::toggleFullScreen()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Cannot toggle full screen");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Fullscreen toggled successfully");

        static bool fullscreen = true;
        unsigned flag = (fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
        fullscreen = !fullscreen;

        SDL_SetWindowFullscreen(window, flag);

    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

void storedStateIsTrue()
{
    if (stored_state)
    {
        stateStack.emplace(stored_state);
        stateStack.top()->start();
        stored_state = nullptr;
    }
    else
    {
        //Nothing to do
    }
}
void runRhythmUpdate()
{
    if (should_rhythm_update)
    {
        should_rhythm_update = false;
        if (off_beat)
        {
            stateStack.top()->rhythmReset();
            std::cout << "." << off_beat << "." << fpb << std::endl;
            fpb = 0;
        }
        else
        {
            stateStack.top()->rhythmUpdate();
            Camera::rhythmUpdate();
        }
    }
    else
    {
        //Nothing to do
    }
}
void checkStateRequested()
{
    if (stateStack.top()->PopRequested() ||
        stateStack.top()->QuitRequested())
    {
        Camera::Follow(nullptr);
        Game::getInstance()->getGridControl()->ClearEnemyVector();
        stateStack.pop();
        Resources::ClearAll();
        if(!stateStack.empty())
        {
            stateStack.top()->Resume();
        }
        else
        {
            //Nothing to do
        }
    }
    else
    {
        //Nothing to do
    }
}
int setDeltaTime(int dt)
{
    if (dt > 1000)
    {
        dt = 1000;
    }
    else
    {
        //Nothing to do
    }
    return dt;
}
void checkInput()
{
    if (input.KeyPress(SDL_SCANCODE_EQUALS))
    {
        adjust += 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }
    else
    {
        //Nothing to do
    }

    if (input.KeyPress(SDL_SCANCODE_MINUS))
    {
        adjust -= 10;
        std::cout << "Adjust = " << adjust << "ms\n";
    }
    else
    {
        //Nothing to do
    }
}
