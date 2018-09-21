#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define INCLUDE_SDL
#include "SDL_include.h"

#include <unordered_map>
#include "Camera.h"

class InputManager {
  public:
    enum Action {
        NONE,
        DIG_DOWN,
        DIG_LEFT,
        DIG_RIGHT,
        DIG_UP,
        ENTER,
        ESCAPE,
        FULLSCREEN,
        ACTION_MAX
    };

    void update(float deltaRhythm);

    bool KeyDown(int key) const { return keyState[key]; }
    bool KeyPress(int key) const {
        return (frame == keyUpdate[key]) && keyState[key];
    }
    bool KeyRelease(int key) const {
        return (frame == keyUpdate[key]) && !keyState[key];
    }

    bool MouseDown(int button) const { return fingerState[button]; }
    bool MousePress(int button) const {
        return (frame == fingerUpdate[button]) && fingerState[button];
    }
    bool MouseRelease(int button) const {
        return (frame == fingerUpdate[button]) && !fingerState[button];
    }

    bool GamepadDown(int button) const { return gamepadState[button]; }
    bool GamepadPress(int button) const {
        return (frame == gamepadUpdate[button]) && gamepadState[button];
    }
    bool GamepadRelease(int button) const {
        return (frame == gamepadUpdate[button]) && !gamepadState[button];
    }

    bool ActionDown(Action button) const { return actionState[button]; }
    bool ActionPress(Action button) const {
        return (frame == actionUpdate[button]) && actionState[button];
    }
    bool ActionRelease(Action button) const {
        return (frame == actionUpdate[button]) && !actionState[button];
    }

    int finger2action(const Vec2& v) const;

    enum mouseKey {
        LEFT = SDL_BUTTON_LEFT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        RIGHT = SDL_BUTTON_RIGHT
    };

    int GetMouseX() const { return mouseX; }
    int GetMouseY() const { return mouseY; }
    Vec2 GetMouse() const { return Vec2(mouseX, mouseY); }
    int GetWorldMouseX() const { return mouseX + Camera::pos.x; }
    int GetWorldMouseY() const { return mouseY + Camera::pos.y; }
    Vec2 GetWorldMouse() const {
        return Vec2(mouseX + Camera::pos.x, mouseY + Camera::pos.y);
    }

    bool QuitRequested() const { return quitRequested; }

    // Meyes' singleton
    static InputManager& GetInstance() {
        static InputManager input;
        return input;
    }

    float scaleFactor() const;

    float GetDeltaRhythm() const { return deltaRhythm; }

    void Move();

    float Moved();

    bool title = true;
    bool shouldShow = true;

  private:
    // Disallow compiler generated ctor, dtor and copy
    InputManager();
    InputManager(InputManager const&);
    InputManager& operator=(InputManager const&);
    ~InputManager() {}

    bool AddController(int id);
    void RemoveController(void);
    SDL_GameController* gameController;

    bool gamepadState[SDL_CONTROLLER_BUTTON_MAX] = {0};
    int gamepadUpdate[SDL_CONTROLLER_BUTTON_MAX] = {0};

    bool keyState[SDL_NUM_SCANCODES] = {0};
    int keyUpdate[SDL_NUM_SCANCODES] = {0};

    bool fingerState[6] = {0};
    int fingerUpdate[6] = {0};

    bool quitRequested = 0;
    int updateCounter = 0;

    int mouseX = 0;
    int mouseY = 0;

    void UpdateKey(int& update, bool& state, bool newValue) const;
    int frame = 0;

    float deltaRhythm = 0;
    float keyAdjust = 0;
    float score = 10;

    bool actionState[Action::ACTION_MAX] = {0};
    int actionUpdate[Action::ACTION_MAX] = {0};
    std::unordered_map<int, Action> gamepad2action;
    std::unordered_map<int, Action> key2action;
};

#endif  // INPUTMANAGER_H
