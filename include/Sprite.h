#pragma once
#define INCLUDE_SDL
#include "Component.h"
#include "SDL_include.h"

class Sprite : public Component {
  public:
    Sprite(GameObject& associated) : Component(associated) {}

    Sprite(GameObject& associated, const std::string& file)
        : Component(associated) {
        Sprite::Open(file);
    }
    ~Sprite() {}

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsOpen() const { return (bool)Sprite::texture; }

    void Update(float dt) {}
    void Render() const;
    bool Is(const std::string& type) const { return !type.compare("Sprite"); }

  private:
    SDL_Texture* texture = nullptr;
    int width;
    int height;

    SDL_Rect clipRect;
};
