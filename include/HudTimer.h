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

    void update(float delta_time);

    void rhythmUpdate() {}
    void render(Common::layer layer) const;

  private:
    void setMeterFrame() const;
    int max_sise = 0;
    float speed = 150;
    std::vector<Vec2> risers = {};
    Sprite *bg, *meter, *fg;
    Rect box_bg, box_meter, box_fg;
    Vec2 off_set1;
    Vec2 off_set2;
    int move_lenght;
    int min_m = 0, max_m = 0;

    InputManager& input;
};

#endif  // HUDTIMER_H
