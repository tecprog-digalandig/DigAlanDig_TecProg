#include "HudCounter.h"
#include "InputManager.h"

HudCounter::HudCounter(GameObject& associated, const std::string& bgFile,
                       const std::string& itemFile)
    : Component(associated) {
    bg = new Sprite(associated, bgFile);
    boxbg = associated.box;

    counter = new Sprite(associated, itemFile, 1);

    offset1 = (boxbg.size - associated.box.size) / 2.0;

    // offset2 = {(internalBox.w - associated.box.w) / 2, 0};
}

HudCounter::~HudCounter() {
    delete bg;
    delete counter;
}

void HudCounter::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);

    associated.box += offset1;

    counter->SetScaleX(2.3 - InputManager::GetInstance().scaleFactor());
    counter->render(layer);
}
