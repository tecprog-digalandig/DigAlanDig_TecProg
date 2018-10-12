#ifndef LIGHT_H
#define LIGHT_H
#include <memory>
#include "Common.h"
#include "Component.h"
#include "Sprite.h"

class Light : public Component {
  public:
    Light(GameObject& associated, std::weak_ptr<GameObject> follow)
        : Component(associated),
          follow(follow),
          sprite(new Sprite(associated, "assets/img/light.png")) {
        sprite->SetBlendMode(SDL_BLENDMODE_ADD);
        sprite->SetColor(255, 255, 255 * 0.8);
        SetSize(600);
    }

    ~Light() { delete sprite; }

    void update(float delta_time) {
        if (auto ptr = follow.lock()) {
            associated.box.SetCenter(ptr->box.Center());
            sprite->update(delta_time);
        } else {
            associated.RequestDelete();
        }
    }

    void rhythmUpdate() {}
    void render(Common::Layer layer) const { sprite->Render(layer); }

    void SetSize(int size) {
        sprite->SetScaleX((double)size / sprite->GetHeight());
    }

    int GetSize() const { return sprite->GetScale().x * sprite->GetHeight(); }

  private:
    std::weak_ptr<GameObject> follow;
    Sprite* sprite;
};

#endif  // LIGHT_H
