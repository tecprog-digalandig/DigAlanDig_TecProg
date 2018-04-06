#pragma once
#define INCLUDE_SDL
#include "Component.h"
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <typeinfo>

class Sprite : public Component {
  public:
    Sprite(GameObject& associated) : Component(associated), texture(nullptr) {}

    Sprite(GameObject& associated, std::string file)
        : Component(associated), texture(nullptr) {
        Sprite::Open(file);
    }
    ~Sprite() {
        if (texture) SDL_DestroyTexture(texture);
    }

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt) {}
    bool Is(std::string type) {
        std::cout << type << std::endl;
        std::cout << typeid(*this).name() << std::endl;
        return !type.compare(typeid(*this).name());
    }

  private:
    SDL_Texture* texture = nullptr;
    int width;
    int height;
    SDL_Rect clipRect;

    SDL_Rect dstRect;
};
