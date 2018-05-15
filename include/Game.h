#ifndef GAME_H
#define GAME_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
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

  private:
    static Game* _instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState = nullptr;
    std::stack<std::unique_ptr<State>> stateStack;

    int frameStart;
    float dt;
    void CalculateDeltaTime();

    Game(const std::string& title, int width, int height);

    InputManager& input;
};

#endif
