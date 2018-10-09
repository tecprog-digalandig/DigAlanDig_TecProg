#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL
#include "SDL_include.h"

#include "Component.h"
#include "Timer.h"

class Sprite : public Component {
  public:
    class SpriteState {
      public:
        std::string file;
        int frameCount;
        int totalFrameCount;
        float frameTime;
    };

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
    void Open(SpriteState sstate, int dir);
    void SetClip(int x, int y, int w, int h) { clipRect = {x, y, w, h}; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsOpen() const { return static_cast<bool>(Sprite::texture); }

    void Update(float dt);
    void AlanUpdate(float dt);
    void RhythmUpdate() {
        if (frameTime == -1)
            SetFrame(((currentFrame - initFrame) + 1) % frameCount + initFrame);
    }
    void RhythmReset() {}
    void Render(Common::Layer layer) const;

    void SetScaleX(double scaleX, double scaleY);
    void SetScaleX(double s) { SetScaleX(s, s); }
    void SetScaleX(const Vec2& v) { SetScaleX(v.x, v.y); }
    Vec2 GetScale() const { return scale; }

    void SetFrame(int frame);
    void SetFrameCount(int frameCount) { this->frameCount = frameCount; }
    void SetFrameTime(float frameTime) { this->frameTime = frameTime; }

    bool FrameTimePassed() {
        if (frameTimeTotal < 0) return false;

        if (timeElapsed < frameTimeTotal)
            return false;
        else {
            return true;
        }
    }

    void SetBlendMode(SDL_BlendMode mode) {
        SDL_SetTextureBlendMode(texture.get(), mode);
    }

    void SetColor(int r, int g, int b) {
        SDL_SetTextureColorMod(texture.get(), r, g, b);
    }

    int GetFrameCount() { return frameCount; }

    void TimeElapsedReset() { timeElapsed = 0; }

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0;
    int height = 0;
    int frameCount = 1;
    int initFrame = 0;
    float frameTime = 1;
    float frameTimeTotal = 1;
    int currentFrame = 0;
    float timeElapsed = 0;
    float secondsToSelfDestruct = 0;
    Timer selfDestructCount;

    SDL_Rect clipRect;
    Vec2 scale;
};

#endif
