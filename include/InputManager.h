#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define INCLUDE_SDL
#include "SDL_include.h"

#include <unordered_map>
#include "Camera.h"

class InputManager {
  public:
    enum action {
        NONE,
        dig_down,
        dig_left,
        dig_right,
        dig_up,
        ENTER,
        ESCAPE,
        FULLSCREEN,
        ACTION_MAX
    };

    void update(float delta_rhythm);

    bool keyDown(int key) const { return key_state[key]; }
    bool keyPress(int key) const {
        return (frame == key_update[key]) && key_state[key];
    }
    bool keyRelease(int key) const {
        return (frame == key_update[key]) && !key_state[key];
    }

    bool mouseDown(int button) const { return finger_state[button]; }
    bool mousePress(int button) const {
        return (frame == finger_update[button]) && finger_state[button];
    }
    bool mouseRelease(int button) const {
        return (frame == finger_update[button]) && !finger_state[button];
    }

    bool gamepadDown(int button) const { return gamepad_state[button]; }
    bool gamepadPress(int button) const {
        return (frame == gamepad_update[button]) && gamepad_state[button];
    }
    bool gamepadRelease(int button) const {
        return (frame == gamepad_update[button]) && !gamepad_state[button];
    }

    bool actionDown(action button) const { return action_state[button]; }
    bool actionPress(action button) const {
        return (frame == action_update[button]) && action_state[button];
    }
    bool actionRelease(action button) const {
        return (frame == action_update[button]) && !action_state[button];
    }

    int finger2action(const Vec2& v) const;

    enum mouseKey {
        left = SDL_BUTTON_LEFT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        right = SDL_BUTTON_RIGHT
    };

    int getMouseX() const { return mouse_x; }
    int getMouseY() const { return mouse_y; }
    Vec2 getMouse() const { return Vec2(mouse_x, mouse_y); }
    int getWorldMouseX() const { return mouse_x + Camera::pos.x; }
    int getWorldMouseY() const { return mouse_y + Camera::pos.y; }
    Vec2 getWorldMouse() const {
        return Vec2(mouse_x + Camera::pos.x, mouse_y + Camera::pos.y);
    }

    bool quitRequested() const { return quit_requested; }

    // Meyes' singleton
    static InputManager& getInstance() {
        static InputManager input;
        return input;
    }

    float scale_factor() const;

    float get_delta_rhythm() const { return delta_rhythm; }

    void move();

    float moved();

    bool title = true;
    bool should_show = true;

  private:
    // Disallow compiler generated ctor, dtor and copy
    InputManager();
    InputManager(InputManager const&);
    InputManager& operator=(InputManager const&);
    ~InputManager() {}

    bool add_controller(int id);
    void remove_controller(void);
    SDL_GameController* game_controller;

    bool gamepad_state[SDL_CONTROLLER_BUTTON_MAX] = {0};
    int gamepad_update[SDL_CONTROLLER_BUTTON_MAX] = {0};

    bool key_state[SDL_NUM_SCANCODES] = {0};
    int key_update[SDL_NUM_SCANCODES] = {0};

    bool finger_state[6] = {0};
    int finger_update[6] = {0};

    bool quit_requested = 0;
    int update_counter = 0;

    int mouse_x = 0;
    int mouse_y = 0;

    void UpdateKey(int& Update, bool& state, bool newValue) const;
    int frame = 0;

    float delta_rhythm = 0;
    float key_adjust = 0;
    float score = 10;

    bool action_state[action::ACTION_MAX] = {0};
    int action_update[action::ACTION_MAX] = {0};
    std::unordered_map<int, action> gamepad2action;
    std::unordered_map<int, action> key2action;
};

#endif
