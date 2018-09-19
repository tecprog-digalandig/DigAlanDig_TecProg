#ifndef GAME_H
#define GAME_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <stack>
#include "GridControl.h"
#include "InputManager.h"
#include "State.h"

class Game
{
    public:
        ~Game();
        void run();
        SDL_Renderer* getRenderer() const { return renderer; }
        State& getCurrentState() const { return *stateStack.top(); }
        GridControl* getGridControl() const { return grid_control; }
        static Game* getInstance() { return _instance; }
        static Game* getInstance(const std::string& title, int w, int h);
        float getDeltaTime() const { return dt; }

        void push(State* state) { stored_state = state; }

        // static std::unordered_map<std::string, int> idata;
        // static std::unordered_map<std::string, std::string> data;
        bool player_victory = false;
        void fixTiming() { adjust = inicial_adjust; }
        void updateBeatTime(int time_rhythm);
        void startBeatTime()
        {
            half_beat_counter = 0;
            tick_counter = 0;
            frame_start = static_cast<int>(SDL_GetTicks());
        }

        int combo = 0;

    private:
        static Game* _instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* stored_state = nullptr;
        GridControl* grid_control = nullptr;
        std::stack<std::unique_ptr<State>> stateStack;

        int frame_start;
        float dt;
        void calculateDeltaTime();
        void toggleFullScreen();

        // TODO move to a configuration file
        static constexpr float bpm = 120;
        static constexpr float bit_rate = 44100;
        int adjust = 0;
        static const int inicial_adjust = 40;

        static const int beat_time = (60 * 1000) / bpm;
        static const int half_beat_time = beat_time / 2;
        int half_beat_counter = 0;
        int tick_counter = 0;
        bool off_beat = false;
        bool should_rhythm_update = false;

        Game(const std::string& title, int width, int height);

        InputManager& input;
        // normalized variable for getting how close a press was to the rhythm
        // 0 = perfect, 1 = worst
        float delta_rhythm = 0;
};

#endif
