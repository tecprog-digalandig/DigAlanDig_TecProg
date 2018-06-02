#include "InputManager.h"

inline void InputManager::UpdateKey(int &update, bool &state,
                                    bool newValue) const {
    if (state != newValue) {
        update = frame;
        state = newValue;
    }
}

float fixRange(float value, float fix) {
    float ret = value + fix;
    if (ret > 1.0)
        ret -= 2;
    else if (ret < -1.0)
        ret += 2;

    return ret;
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

    if (KeyPress(SDL_SCANCODE_0)) {
        keyAdjust += 0.05;
        std::cout << "\nKey Adjust = " << keyAdjust << "ms\n";
    }
    if (KeyPress(SDL_SCANCODE_9)) {
        keyAdjust -= 0.05;
        std::cout << "\nKey Adjust = " << keyAdjust << "ms\n";
    }
}
