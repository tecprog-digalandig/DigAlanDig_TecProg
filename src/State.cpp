#include "State.h"
#include "SDL2/SDL.h"

#define UNUSED_VAR (void)

State::State(void) {
    bg = new Sprite("assets/img/ocean.jpg");
    music = new Music("assets/audio/stageState.ogg");
    music->Play(2);
    quitRequested = false;
}

State::~State(void) { delete bg; }

bool State::QuitRequested(void) { return quitRequested; }

void State::Update(float dt) {
    if (SDL_QuitRequested()) quitRequested = true;
}

void State::Render(void) { bg->Render(0, 0); }
