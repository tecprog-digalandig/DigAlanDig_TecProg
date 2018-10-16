#include "HudMeter.h"
#include "Alan.h"
#include "InputManager.h"

HudMeter::HudMeter(GameObject& associated, const std::string& bgFile,
                   const std::string& meterFile)
    : Component(associated) {
    bg = new Sprite(associated, bgFile);
    boxbg = associated.box;

    meter = new Sprite(associated, meterFile, 3, 1e9);
    Rect meterBox = associated.box;

    int margin = 50 - meterBox.w;
    Rect internalBox = boxbg;
    internalBox.w -= 2 * margin;

    offset1.y = (boxbg.h - meterBox.h) / 2.0;
    offset1.x = margin;

    offset2 = {(internalBox.w - associated.box.w) / 2, 0};
}

HudMeter::~HudMeter() {
    delete bg;
    delete meter;
}

void HudMeter::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);

    associated.box += offset1;

    float s = InputManager::GetInstance().scaleFactor();
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
        tmp = alan.lock()->getComponent<Alan*>()->GetHP() - i * 2;
    else {
        if (!Game::GetInstance()->combo)
            tmp = 0;
        else
            tmp =
                (int)floor(Game::GetInstance()->combo / (5 * (i + 1))) - i + 1;
    }

    if (tmp >= 2)
        meter->setFrame(2);
    else if (tmp == 1)
        meter->setFrame(1);
    else
        meter->setFrame(0);
}
