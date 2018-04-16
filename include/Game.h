#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"

class Game {
  public:
    ~Game(void);
    void run(void);
    SDL_Renderer* getRenderer(void) const { return renderer; }
    State* getState(void) const { return state; }
    static Game* getInstance(void) { return _instance; }
    static Game* getInstance(const std::string& title, int w, int h);

  private:
    static Game* _instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game(const std::string& title, int width, int height);
};
