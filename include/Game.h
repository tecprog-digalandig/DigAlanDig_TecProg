#ifndef GAME_H
#define GAME_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <stack>
#include "InputManager.h"
#include "SDL_include.h"
#include "State.h"

class Game {
  public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer() const { return renderer; }
    State& GetCurrentState() const { return *stateStack.top(); }
    static Game* GetInstance() { return _instance; }
    static Game* GetInstance(const std::string& title, int w, int h);
    float GetDeltaTime() const { return dt; }

    void Push(State* state) { storedState = state; }

    // static std::unordered_map<std::string, int> idata;
    // static std::unordered_map<std::string, std::string> data;
    bool playerVictory = false;

  private:
    static Game* _instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState = nullptr;
    std::stack<std::unique_ptr<State>> stateStack;

    int frameStart;
    float dt;
    void CalculateDeltaTime();

    // TODO move to a configuration file
    static constexpr float bpm = 120;
    int adjust = 200;
    int keyAdjust = 0;

    static const int beatTime = (60 * 1000) / bpm;
    int beatCounter = 0;
    bool shouldRhythmUpdate = false;

    Game(const std::string& title, int width, int height);

    InputManager& input;
    bool musicPlaying = false;
    // normalized variable for getting how close a press was to the rhythm
    // 0 = perfect, 1 = worst
    float deltaRhythm = 0;
};

#endif
