#ifndef PARALLAX_H
#define PARALLAX_H
#include "Camera.h"
#include "Component.h"

class ParallaxY : public Component {
  public:
    ParallaxY(GameObject& associated, float factor = 1)
        : Component(associated), factor(factor) {}

    void Update(float delta_time) { associated.box.pos.y = -Camera::pos.y * factor; }
    void rhythmUpdate() {}
    void render(Common::Layer layer) const {}

  private:
    float factor;
};

class bgCircularY : public Component {
  public:
    bgCircularY(GameObject& associated, const std::string& file)
        : Component(associated) {
        Open(file);
    }

    void Open(const std::string& file);
    void Update(float delta_time) {}
    void rhythmUpdate() {}
    void render(Common::Layer layer) const;

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0, height = 0;
};

class bgCircularX : public Component {
  public:
    bgCircularX(GameObject& associated, const std::string& file)
        : Component(associated) {
        Open(file);
    }

    void Open(const std::string& file);
    void Update(float delta_time) {}
    void rhythmUpdate() {}
    void render(Common::Layer layer) const;
    int GetWidth() { return width; }

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0, height = 0;
};

class ParallaxX : public Component {
  public:
    ParallaxX(GameObject& associated, float factor = 1)
        : Component(associated), factor(factor) {}

    void Update(float delta_time) { associated.box.pos.x -= delta_time * factor * 10; }
    void rhythmUpdate() {}
    void render(Common::Layer layer) const {}

  private:
    float factor;
};

#endif  // PARALLAX_H
