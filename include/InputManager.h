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

    void update(float delta_rhythm);

    bool key_down(int key) const { return key_state[key]; }
    bool key_press(int key) const {
        return (frame == key_update[key]) && key_state[key];
    }
    bool key_release(int key) const {
        return (frame == key_update[key]) && !key_state[key];
    }

    bool mouse_down(int button) const { return finger_state[button]; }
    bool mouse_press(int button) const {
        return (frame == finger_update[button]) && finger_state[button];
    }
    bool mouse_release(int button) const {
        return (frame == finger_update[button]) && !finger_state[button];
    }

    bool gamepad_down(int button) const { return gamepad_state[button]; }
    bool gamepad_press(int button) const {
        return (frame == gamepad_update[button]) && gamepad_state[button];
    }
    bool gamepad_release(int button) const {
        return (frame == gamepad_update[button]) && !gamepad_state[button];
    }

    bool action_down(Action button) const { return action_state[button]; }
    bool action_press(Action button) const {
        return (frame == action_update[button]) && action_state[button];
    }
    bool action_release(Action button) const {
        return (frame == action_update[button]) && !action_state[button];
    }

    int finger2action(const Vec2& v) const;

    enum mouse_key {
        LEFT = SDL_BUTTON_LEFT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        RIGHT = SDL_BUTTON_RIGHT
    };

    int get_mouse_x() const { return mouse_x; }
    int get_mouse_y() const { return mouse_y; }
    Vec2 get_mouse() const { return Vec2(mouse_x, mouse_y); }
    int get_world_mouse_x() const { return mouse_x + Camera::pos.x; }
    int get_world_mouse_y() const { return mouse_y + Camera::pos.y; }
    Vec2 get_world_mouse() const {
        return Vec2(mouse_x + Camera::pos.x, mouse_y + Camera::pos.y);
    }

    bool quit_requested() const { return quit_requested; }

    // Meyes' singleton
    static InputManager& get_instance() {
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

    void update_key(int& update, bool& state, bool newValue) const;
    int frame = 0;

    float delta_rhythm = 0;
    float key_adjust = 0;
    float score = 10;

    bool action_state[Action::ACTION_MAX] = {0};
    int action_update[Action::ACTION_MAX] = {0};
    std::unordered_map<int, Action> gamepad2action;
    std::unordered_map<int, Action> key2action;
};

#endif
