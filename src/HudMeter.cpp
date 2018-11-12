#include "HudMeter.h"
#include "Alan.h"
#include "InputManager.h"

HudMeter::HudMeter(GameObject& associated, const std::string& bg_file,
                   const std::string& meter_file)
    : Component(associated)
{
    bg = new Sprite(associated, bg_file);
    boxbg = associated.box;
    meter = new Sprite(associated, meter_file, 3, 1e9);
    Rect meter_box = associated.box;
    int margin = 50 - meter_box.w;
    Rect internal_box = boxbg;
    internal_box.w -= 2 * margin;
    offset1.y = (boxbg.h - meter_box.h) / 2.0;
    offset1.x = margin;
    offset2 = {(internal_box.w - associated.box.w) / 2, 0};
}

HudMeter::~HudMeter()
{
    delete bg;
    delete meter;
}

void HudMeter::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);

    associated.box += offset1;

    float s = InputManager::getInstance().scaleFactor();
    for (int i = 0; i < 3; i++) {
        setMeter(i);
        meter->SetScaleX(s);
        meter->render(layer);
        associated.box += offset2;
    }
}

void HudMeter::setMeter(int i) const {
    int tmp;
    if (isHeart)
        tmp = alan.lock()->GetComponent<Alan*>()->getHP() - i * 2;
    else {
        if (!Game::getInstance()->combo)
            tmp = 0;
        }
        else
        {
            tmp =
                (int)floor(Game::GetInstance()->combo / (5 * (i + 1))) - i + 1;
        }
    }

    if (tmp >= 2)
    {
        meter->SetFrame(2);
    }
    else if (tmp == 1)
    {
        meter->SetFrame(1);
    }
    else
    {
        meter->SetFrame(0);
    }
}
