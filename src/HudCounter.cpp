/**
* @file HudCounter.cpp
* @copyright 2018 Pedro H.
* @brief Class that inicializes heads-up display counting numbers on the screen,
* such as the number of minerals the character is getting.
*/

#include "HudCounter.h"
#include "InputManager.h"
#include <assert.h>

HudCounter::HudCounter(GameObject& associated, const std::string& bgFile,
                       const std::string& itemFile) : Component(associated)
{
    assert(associated != nullptr);
    assert(bgFile != nullptr);

    bg = new Sprite(associated, bgFile);
    assert(bg != nullptr);

    boxbg = associated.box;

    counter = new Sprite(associated, itemFile, 1);
    assert(counter != nullptr);

    offset1 = (boxbg.size - associated.box.size) / 2.0;

}


void HudCounter::Render(Common::Layer layer) const
{
    associated.box = boxbg;
    bg->Render(layer);

    associated.box += offset1;

    counter->SetScaleX(2.3 - InputManager::GetInstance().scaleFactor());
    counter->Render(layer);
}

HudCounter::~HudCounter()
{
    delete bg;
    delete counter;

    assert(bg == nullptr);
    assert(counter == nullptr);
}
