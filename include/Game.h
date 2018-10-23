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

class Game {
  public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer() const { return renderer; }
    State& getCurrentState() const { return *stateStack.top(); }
    GridControl* getGridControl() const { return gridControl; }
    static Game* getInstance() { return _instance; }
    static Game* getInstance(const std::string& title, int w, int h);
    float GetDeltaTime() const { return delta_time; }

    void Push(State* state) { storedState = state; }

    // static std::unordered_map<std::string, int> idata;
    // static std::unordered_map<std::string, std::string> data;
    bool playerVictory = false;
    void FixTiming() { adjust = inicialAdjust; }
    void UpdateBeatTime(int timeRhythm);
    void StartBeatTime() {
        halfBeatCounter = 0;
        tickCounter = 0;
        frameStart = static_cast<int>(SDL_GetTicks());
    }

    int combo = 0;

  private:
    static Game* _instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState = nullptr;
    GridControl* gridControl = nullptr;
    std::stack<std::unique_ptr<State>> stateStack;

    int frameStart;
    float delta_time;
    void CalculateDeltaTime();
    void ToggleFullScreen();

    // TODO move to a configuration file
    static constexpr float bpm = 120;
    static constexpr float bitRate = 44100;
    int adjust = 0;
    static const int inicialAdjust = 40;

    static const int beatTime = (60 * 1000) / bpm;
    static const int halfBeatTime = beatTime / 2;
    int halfBeatCounter = 0;
    int tickCounter = 0;
    bool offBeat = false;
    bool shouldrhythmUpdate = false;

    Game(const std::string& title, int width, int height);

    InputManager& input;
    // normalized variable for getting how close a press was to the rhythm
    // 0 = perfect, 1 = worst
    float deltaRhythm = 0;
};

#endif
