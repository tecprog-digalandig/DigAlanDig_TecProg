#include "HudTimer.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;
HudTimer::HudTimer(GameObject& associated)
    : Component(associated), input(InputManager::GetInstance()) {
    Vec2 center = associated.box.Center();

    bg = new Sprite(associated, "assets/hud/timerbg.png");
    associated.box.SetCenter(center);
    boxbg = associated.box;

    meter = new Sprite(associated, "assets/hud/raio.png", 3, 1e9);
    associated.box.SetCenter(center);
    boxmeter = associated.box;

    fg = new Sprite(associated, "assets/hud/timerfg.png");
    associated.box.SetCenter(center);
    boxfg = associated.box;

    moveLenght = boxbg.w / 2 - boxmeter.w / 2;

    minM = boxmeter.x + moveLenght * -0.5;
    maxM = boxmeter.x + moveLenght * 0.5;
}

void HudTimer::render(Common::Layer layer) const {
    associated.box = boxbg;
    bg->render(layer);
    spdlog::get("log")->info("Render timer");  //T29

    associated.box = boxmeter;
    associated.box.x += moveLenght * -input.GetDeltaRhythm();
    SetMeterFrame();
    meter->render(layer);
    spdlog::get("log")->info("Render raio");  //T29

    for (auto rise : risers) {
        associated.box.pos = rise;
        SetMeterFrame();
        meter->render(layer);
    }

    associated.box = boxfg;
    fg->render(layer);
    spdlog::get("log")->info("Render central timer");  //T29

}

void HudTimer::SetMeterFrame() const {
    if (associated.box.x < maxM && associated.box.x > minM) {
        meter->SetFrame(2);
        meter->SetScaleX(1.5);
    } else {
        meter->SetFrame(0);
        meter->SetScaleX(0.8);
    }
}

void HudTimer::update(float dt) {
    if (abs(input.GetDeltaRhythm()) < 0.5) {
        meter->SetFrame(2);
        meter->SetScaleX(1.5);
    } else {
        meter->SetFrame(0);
        meter->SetScaleX(0.8);
    }

    float mov = input.Moved();
    if (mov < 1.1) {
        
        spdlog::get("console")->info("Move: {}", mov);  //T29
        spdlog::get("log")->info("Move: {}", mov);  //T29

        Vec2 rise(boxmeter.pos + Vec2(moveLenght, 0) * -mov);
        risers.push_back(rise);
    }

    for (auto& rise : risers) {
        rise.y -= dt * speed;
    }

    risers.erase(remove_if(risers.begin(), risers.end(),
                                [](Vec2 v) { return v.y < 570; }),
                 risers.end());
}
