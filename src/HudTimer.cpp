#include "HudTimer.h"

HudTimer::HudTimer(GameObject& associated)
    : Component(associated), input(InputManager::getInstance()) {
    Vec2 center = associated.box.Center();

    bg = new Sprite(associated, "assets/hud/timerbg.png");
    associated.box.setCenter(center);
    boxbg = associated.box;

    meter = new Sprite(associated, "assets/hud/raio.png", 3, 1e9);
    associated.box.setCenter(center);
    boxmeter = associated.box;

    fg = new Sprite(associated, "assets/hud/timerfg.png");
    associated.box.setCenter(center);
    boxfg = associated.box;

    moveLenght = boxbg.w / 2 - boxmeter.w / 2;

    minM = boxmeter.x + moveLenght * -0.5;
    maxM = boxmeter.x + moveLenght * 0.5;
}

void HudTimer::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);

    associated.box = boxmeter;
    associated.box.x += moveLenght * -input.getDeltaRhythm();
    SetMeterFrame();
    meter->render(layer);

    for (auto rise : risers) {
        associated.box.pos = rise;
        SetMeterFrame();
        meter->render(layer);
    }

    associated.box = boxfg;
    fg->render(layer);
}

void HudTimer::SetMeterFrame() const {
    if (associated.box.x < maxM && associated.box.x > minM) {
        meter->setFrame(2);
        meter->SetScaleX(1.5);
    } else {
        meter->setFrame(0);
        meter->SetScaleX(0.8);
    }
}

void HudTimer::Update(float delta_time) {
    if (std::abs(input.getDeltaRhythm()) < 0.5) {
        meter->setFrame(2);
        meter->SetScaleX(1.5);
    } else {
        meter->setFrame(0);
        meter->SetScaleX(0.8);
    }

    float mov = input.Moved();
    if (mov < 1.1) {
        std::cout << "Mov" << mov << std::endl;
        Vec2 rise(boxmeter.pos + Vec2(moveLenght, 0) * -mov);
        risers.push_back(rise);
    }

    for (auto& rise : risers) {
        rise.y -= delta_time * speed;
    }

    risers.erase(std::remove_if(risers.begin(), risers.end(),
                 [](Vec2 v) { return v.y < 570; }),
                 risers.end());
}
