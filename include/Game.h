#ifndef GAME_H
#define GAME_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"

class Game {
  public:
    ~Game(void);
    void Run(void);
    SDL_Renderer* GetRenderer(void) const { return renderer; }
    State* GetState(void) const { return state; }
    static Game* GetInstance(void) { return _instance; }
    static Game* GetInstance(const std::string& title, int w, int h);
    float GetDeltaTime() const { return dt; }

  private:
    static Game* _instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state = nullptr;

    int frameStart;
    float dt;
    void CalculateDeltaTime();

    Game(const std::string& title, int width, int height);
};

#endif
