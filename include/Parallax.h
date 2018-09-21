#ifndef PARALLAX_H
#define PARALLAX_H
#include "Camera.h"
#include "Component.h"

/**
 * @brief Describe methods and atribute of class ParalaxY.
 * 
 */
class ParallaxY : public Component {
  public:
    ParallaxY(GameObject& associated, float factor = 1)
        : Component(associated), factor(factor) {}

    void Update(float dt) { associated.box.pos.y = -Camera::pos.y * factor; }
    void RhythmUpdate() {}
    void Render(Common::Layer layer) const {}

  private:
    float factor;
};


/**
 * @brief Describe methods and atribute of class bgCircularY.
 * 
 */
class bgCircularY : public Component {
  public:
    bgCircularY(GameObject& associated, const std::string& file)
        : Component(associated) {
        Open(file);
    }

    void Open(const std::string& file);
    void Update(float dt) {}
    void RhythmUpdate() {}
    void Render(Common::Layer layer) const;

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0, height = 0;
};


/**
 * @brief Describe methods and atribute of class bgCircularX. 
 * 
 */
class bgCircularX : public Component {
  public:
    bgCircularX(GameObject& associated, const std::string& file)
        : Component(associated) {
        Open(file);
    }

    void Open(const std::string& file);
    void Update(float dt) {}
    void RhythmUpdate() {}
    void Render(Common::Layer layer) const;
    int GetWidth() { return width; }

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0, height = 0;
};


/**
 * @brief Describe methods and atribute of class ParalaxX.
 * 
 */
class ParallaxX : public Component {
  public:
    ParallaxX(GameObject& associated, float factor = 1)
        : Component(associated), factor(factor) {}

    void Update(float dt) { associated.box.pos.x -= dt * factor * 10; }
    void RhythmUpdate() {}
    void Render(Common::Layer layer) const {}

  private:
    float factor;
};

#endif  // PARALLAX_H
