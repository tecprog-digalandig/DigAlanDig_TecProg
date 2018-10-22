#ifndef HUDMETER_H
#define HUDMETER_H
#include <iostream>
#include "Component.h"
#include "Sprite.h"

class HudMeter : public Component {
  public:
    HudMeter(GameObject& associated, const std::string& bg_file,
             const std::string& meter_file);
    ~HudMeter();

    void update(float dt) {}

    void rhythmUpdate() {}
    void render(Common::Layer layer) const;

    void SetAlan(std::weak_ptr<GameObject> alan) 
    { 
      this->alan = alan;
    }
    void setIsHeart(bool isHeart) 
    { 
      this->isHeart = isHeart;
    }

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

class HeartMeter : public HudMeter 
{
  public:
    HeartMeter(GameObject& associated, const std::string& bg_file,
               const std::string& meter_file)
        : HudMeter(associated, bg_file, meter_file){};
};

class LightMeter : public HudMeter 
{
  public:
    LightMeter(GameObject& associated, const std::string& bg_file,
               const std::string& meter_file)
        : HudMeter(associated, bg_file, meter_file){};
};

#endif  // HUDMETER_H
