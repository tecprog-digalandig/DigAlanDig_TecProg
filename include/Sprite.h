#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL
#include "Component.h"
#include "SDL_include.h"
#include "Timer.h"

class Sprite : public Component {
  public:
    explicit Sprite(GameObject& associated)
        : Component(associated), scale(1, 1) {}

    Sprite(GameObject& associated, const std::string& file, int frameCount = 1,
           float frameTime = 1, float secondsToSelfDestruct = 0)
        : Component(associated),
          frameCount(frameCount),
          frameTime(frameTime),
          secondsToSelfDestruct(secondsToSelfDestruct),
          scale(1, 1) {
        Sprite::Open(file);
    }
    ~Sprite() {}

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h) { clipRect = {x, y, w, h}; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsOpen() const { return static_cast<bool>(Sprite::texture); }

    void Update(float dt);
    void Render() const;
    bool Is(const std::string& type) const { return !type.compare("Sprite"); }

    void SetScaleX(double scaleX, double scaleY);
    void SetScaleX(const Vec2& v) { SetScaleX(v.x, v.y); }
    Vec2 GetScale() const { return scale; }

    void SetFrame(int frame);
    void SetFrameCount(int frameCount) { this->frameCount = frameCount; }
    void SetFrameTime(float frameTime) { this->frameTime = frameTime; }

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0;
    int height = 0;
    int frameCount = 0;
    float frameTime = 0;
    int currentFrame = 0;
    float timeElapsed = 0;
    float secondsToSelfDestruct = 1;
    Timer selfDestructCount;

    SDL_Rect clipRect;
    Vec2 scale;
};

#endif
