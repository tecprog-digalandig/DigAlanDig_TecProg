#include "InputManager.h"
InputManager::InputManager() {
    key2action[SDL_SCANCODE_ESCAPE] = Action::ESCAPE;
    key2action[SDL_SCANCODE_AC_BACK] = Action::ESCAPE;
    gamepad2action[SDL_CONTROLLER_BUTTON_BACK] = Action::ESCAPE;

    key2action[SDL_SCANCODE_RETURN] = Action::ENTER;
    key2action[SDL_SCANCODE_SPACE] = Action::ENTER;
    gamepad2action[SDL_CONTROLLER_BUTTON_START] = Action::ENTER;

    key2action[SDL_SCANCODE_DOWN] = Action::DIG_DOWN;
    gamepad2action[SDL_CONTROLLER_BUTTON_A] = Action::DIG_DOWN;
    gamepad2action[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = Action::DIG_DOWN;

    key2action[SDL_SCANCODE_LEFT] = Action::DIG_LEFT;
    gamepad2action[SDL_CONTROLLER_BUTTON_X] = Action::DIG_LEFT;
    gamepad2action[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = Action::DIG_LEFT;

    key2action[SDL_SCANCODE_UP] = Action::DIG_UP;
    gamepad2action[SDL_CONTROLLER_BUTTON_Y] = Action::DIG_UP;
    gamepad2action[SDL_CONTROLLER_BUTTON_DPAD_UP] = Action::DIG_UP;

    key2action[SDL_SCANCODE_RIGHT] = Action::DIG_RIGHT;
    gamepad2action[SDL_CONTROLLER_BUTTON_B] = Action::DIG_RIGHT;
    gamepad2action[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = Action::DIG_RIGHT;

    key2action[SDL_SCANCODE_F] = Action::FULLSCREEN;
    gamepad2action[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = Action::FULLSCREEN;
}

int InputManager::finger2action(const Vec2 &v) const {
    if (title) return Action::ENTER;
    if (v.x < 0.15) return Action::DIG_LEFT;
    if (v.x > 0.85) return Action::DIG_RIGHT;
    if (v.y > 0.5) return Action::DIG_DOWN;
    if (v.y > 0.1) return Action::DIG_UP;
    return Action::ESCAPE;
}

inline void InputManager::UpdateKey(int &update, bool &state,
                                    bool newValue) const {
    if (state != newValue) {
        update = frame;
        state = newValue;
    }
}

float InputManager::scaleFactor() const {
    float dR = GetDeltaRhythm();
    static constexpr float maxS = 0.3;
    float scale = pow(10, -(std::abs(dR) - 1)) / 10;
    if (scale > 0.8) scale += 0.5;
    return scale * maxS + 1;
}

float fixRange(float value, float fix) {
    float ret = value + fix;
    if (ret > 1.0)
        ret -= 2;
    else if (ret < -1.0)
        ret += 2;

    return ret;
}

void InputManager::update(float deltaRhythm) {
    frame++;
    quitRequested = false;

#ifdef __ANDROID__
    this->deltaRhythm = fixRange(deltaRhythm, 0.6);
#else
    this->deltaRhythm = fixRange(deltaRhythm, -0.4);
#endif

    SDL_GetMouseState(&mouseX, &mouseY);
    int id;
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
                UpdateKey(actionUpdate[key2action[event.key.keysym.scancode]],
                          actionState[key2action[event.key.keysym.scancode]],
                          event.type == SDL_KEYDOWN);
                break;

            case SDL_FINGERDOWN:
            case SDL_FINGERUP:
                id = finger2action(Vec2(event.tfinger.x, event.tfinger.y));
                UpdateKey(actionUpdate[id], actionState[id],
                          event.type == SDL_FINGERDOWN);
                break;

            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                UpdateKey(gamepadUpdate[event.cbutton.button],
                          gamepadState[event.cbutton.button],
                          event.type == SDL_CONTROLLERBUTTONDOWN);
                UpdateKey(actionUpdate[gamepad2action[event.cbutton.button]],
                          actionState[gamepad2action[event.cbutton.button]],
                          event.type == SDL_CONTROLLERBUTTONDOWN);
                break;

            case SDL_CONTROLLERDEVICEADDED:
                AddController(event.cdevice.which);
                std::cout << "control pad: "
                          << SDL_GameControllerName(gameController)
                          << std::endl;
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                RemoveController();
                break;
        }
    }

    if (GamepadPress(SDL_CONTROLLER_BUTTON_LEFTSTICK)) Camera::Shake(4, 0.1);
    if (KeyPress(SDL_SCANCODE_5)) Camera::Shake(4, 0.1);

    if (KeyPress(SDL_SCANCODE_0)) {
        keyAdjust += 0.05;
        std::cout << "\nKey Adjust = " << keyAdjust << "ms\n";
    }
    if (KeyPress(SDL_SCANCODE_9)) {
        keyAdjust -= 0.05;
        std::cout << "\nKey Adjust = " << keyAdjust << "ms\n";
    }
}

void InputManager::Move() { score = deltaRhythm; }

float InputManager::Moved() {
    float tmp = score;
    score = 10;
    return tmp;
}

bool InputManager::AddController(int id) {
    if (SDL_IsGameController(id)) {
        SDL_GameControllerClose(gameController);
        gameController = SDL_GameControllerOpen(id);
        if (gameController == NULL)
            std::cout << "SDL GameController(" << id
                      << ") Error: " << SDL_GetError() << std::endl;
        return true;
    }
    std::cout << "Controller not suported" << std::endl;

    return false;
}

void InputManager::RemoveController(void) {
    SDL_GameControllerClose(gameController);
}
