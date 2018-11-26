#ifndef HUDTIMER_H
#define HUDTIMER_H
#include "Common.h"
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"

class HudTimer : public Component {
  public:
    explicit HudTimer(GameObject& associated);
    ~HudTimer() {}

    void update(float dt);

    void rhythmUpdate() {}
    void render(Common::Layer layer) const;

  private:
    void SetMeterFrame() const;
    int maxRise = 0;
    float speed = 150;
    std::vector<Vec2> risers = {};
    Sprite *bg, *meter, *fg;
    Rect boxbg, boxmeter, boxfg;
    Vec2 offset1;
    Vec2 offset2;
    int moveLenght;
    int minM = 0, maxM = 0;

    InputManager& input;
};

#endif  // HUDTIMER_H
