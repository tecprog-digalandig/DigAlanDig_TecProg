#include "InputManager.h"

inline void InputManager::UpdateKey(int &update, bool &state,
                                    bool newValue) const {
    if (state != newValue) {
        update = frame;
        state = newValue;
    }
}

void InputManager::Update(float deltaRhythm) {
    frame++;
    quitRequested = false;
    this->deltaRhythm = deltaRhythm;
    std::cout << deltaRhythm << ' ';

    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Se o evento for quit, setar a flag para terminação
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                UpdateKey(keyUpdate[event.key.keysym.scancode],
                          keyState[event.key.keysym.scancode],
                          event.type == SDL_KEYDOWN);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                UpdateKey(mouseUpdate[event.button.button],
                          mouseState[event.button.button],
                          event.type == SDL_MOUSEBUTTONDOWN);
                break;
        }
    }
}
