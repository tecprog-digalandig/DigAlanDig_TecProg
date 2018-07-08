#ifndef HUDMETER_H
#define HUDMETER_H
#include <iostream>
#include "Component.h"
#include "Sprite.h"

class HudMeter : public Component {
  public:
    HudMeter(GameObject& associated, const std::string& bgFile,
             const std::string& meterFile);
    ~HudMeter();

    void Update(float dt) {}

    void RhythmUpdate() {}
    void Render(Common::Layer layer) const;

    void SetAlan(std::weak_ptr<GameObject> alan) { this->alan = alan; }
    void setIsHeart(bool isHeart) { this->isHeart = isHeart; }

    void setLevel(int level);

  private:
    bool isHeart = false;
    std::weak_ptr<GameObject> alan;
    Sprite *bg, *meter;
    Rect boxbg;
    Vec2 offset1;
    Vec2 offset2;

    void setMeter(int i) const;
};

class HeartMeter : public HudMeter {
  public:
    HeartMeter(GameObject& associated, const std::string& bgFile,
               const std::string& meterFile)
        : HudMeter(associated, bgFile, meterFile){};
};

class LightMeter : public HudMeter {
  public:
    LightMeter(GameObject& associated, const std::string& bgFile,
               const std::string& meterFile)
        : HudMeter(associated, bgFile, meterFile){};
};

#endif  // HUDMETER_H
