#include "HudCounter.h"
#include "InputManager.h"

HudCounter::HudCounter(GameObject& associated, const std::string& bgFile,
                       const std::string& itemFile) : Component(associated)
    {
        bg = new Sprite(associated, bgFile);
        boxbg = associated.box;

        counter = new Sprite(associated, itemFile, 1);

        offset1 = (boxbg.size - associated.box.size) / 2.0;

    }

HudCounter::~HudCounter()
{
    delete bg;
    delete counter;
}

void HudCounter::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);

    associated.box += offset1;

<<<<<<< HEAD
    counter->SetScaleX(2.3 - InputManager::getInstance().scaleFactor());
=======
    counter->SetScaleX(2.3 - InputManager::GetInstance().scaleFactor());
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
    counter->render(layer);
}
