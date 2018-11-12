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
          sprite(new Sprite(associated, "assets/img/light.png"))
    {
        sprite->setBlendMode(SDL_BLENDMODE_ADD);
        sprite->setColor(255, 255, 255 * 0.8);
        setSize(600);
    }

    ~Light()
    {
        delete sprite;
    }

    void update(float delta_time) {
        if (auto ptr = follow.lock()) {
            associated.box.setCenter(ptr->box.Center());
            sprite->update(delta_time);
        } else {
            associated.requestDelete();
            }
    }

    void rhythmUpdate() {}
    void render(Common::layer layer) const { sprite->render(layer); }

    void setSize(int size)
    {
        sprite->setScaleX((double)size / sprite->GetHeight());
    }

    int getSize() const
    {
        return sprite->getScale().x * sprite->GetHeight();
    }

  private:
    std::weak_ptr<GameObject> follow;
    Sprite* sprite;
};

#endif  // LIGHT_H
