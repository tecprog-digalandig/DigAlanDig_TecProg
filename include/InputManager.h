#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Camera.h"
#include "SDL2/SDL.h"

class InputManager {
  public:
    void Update();

    bool IsKeyDown(int key) const { return keyState[key]; }
    bool KeyPress(int key) const {
        return (frame == keyUpdate[key]) && keyState[key];
    }
    bool KeyRelease(int key) const {
        return (frame == keyUpdate[key]) && !keyState[key];
    }

    bool IsMouseDown(int button) const { return mouseState[button]; }
    bool MousePress(int button) const {
        return (frame == mouseUpdate[button]) && mouseState[button];
    }
    bool MouseRelease(int button) const {
        return (frame == mouseUpdate[button]) && !mouseState[button];
    }

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

  private:
    // Disallow compiler generated ctor, dtor and copy
    InputManager() {}
    InputManager(InputManager const&);
    InputManager& operator=(InputManager const&);
    ~InputManager() {}

    bool keyState[SDL_NUM_SCANCODES] = {0};
    int keyUpdate[SDL_NUM_SCANCODES] = {0};

    bool mouseState[6] = {0};
    int mouseUpdate[6] = {0};

    bool quitRequested = 0;
    int updateCounter = 0;

    int mouseX = 0;
    int mouseY = 0;

    void UpdateKey(int& update, bool& state, bool newValue);
    int frame = 0;
};

#endif  // INPUTMANAGER_H
