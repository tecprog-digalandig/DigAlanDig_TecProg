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

    void Update(float dt);

    void RhythmUpdate() {}
    void Render(Common::Layer layer) const;

  private:
    Sprite *bg, *meter, *fg;
    Rect boxbg, boxmeter, boxfg;
    Vec2 offset1;
    Vec2 offset2;
    int moveLenght;

    InputManager& input;
};

#endif  // HUDTIMER_H
