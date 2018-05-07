#pragma once
#define INCLUDE_SDL
#include "Component.h"
#include "SDL_include.h"

class Sprite : public Component {
  public:
    Sprite(GameObject& associated) : Component(associated), scale(1, 1) {}

    Sprite(GameObject& associated, const std::string& file)
        : Component(associated), scale(1, 1) {
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

    void setScaleX(float scaleX, float scaleY);
    void setScaleX(const Vec2& v) { setScaleX(v.x, v.y); }
    Vec2 getScale() const { return scale; }

  private:
    SDL_Texture* texture = nullptr;
    int width;
    int height;

    SDL_Rect clipRect;
    Vec2 scale;
};
