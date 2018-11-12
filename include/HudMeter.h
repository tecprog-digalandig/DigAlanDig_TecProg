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

    void update(float delta_time) {}

    void rhythmUpdate() {}
    void render(Common::layer layer) const;

    void setAlan(std::weak_ptr<GameObject> alan)
    {
      this->alan = alan;
    }
    void setIsHeart(bool is_heart)
    {
      this->is_heart = is_heart;
    }

    void setLevel(int level);

  private:
    bool is_heart = false;
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
