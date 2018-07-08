#include "HudTimer.h"

HudTimer::HudTimer(GameObject& associated)
    : Component(associated), input(InputManager::GetInstance()) {
    Vec2 center = associated.box.Center();

    bg = new Sprite(associated, "assets/hud/timerbg.png");
    associated.box.SetCenter(center);
    boxbg = associated.box;

    meter = new Sprite(associated, "assets/hud/coracao.png", 3, 1e9);
    associated.box.SetCenter(center);
    boxmeter = associated.box;

    fg = new Sprite(associated, "assets/hud/timerfg.png");
    associated.box.SetCenter(center);
    boxfg = associated.box;

    moveLenght = boxbg.w / 2 - boxmeter.w / 2;
}

void HudTimer::Render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->Render(layer);

    associated.box = boxmeter;
    associated.box.x += moveLenght * -input.GetDeltaRhythm();
    meter->Render(layer);

    associated.box = boxfg;
    fg->Render(layer);
}

void HudTimer::Update(float dt) {
    if (std::abs(input.GetDeltaRhythm()) < 0.5) {
        meter->SetFrame(2);
        meter->SetScaleX(1.5);
    } else {
        meter->SetFrame(0);
        meter->SetScaleX(0.8);
    }
}
