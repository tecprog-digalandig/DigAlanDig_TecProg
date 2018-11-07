#ifndef HUDCOUNTER_H
#define HUDCOUNTER_H
#include "Component.h"
#include "Sprite.h"

class HudCounter : public Component
{
    public:
        HudCounter(GameObject& associated, const std::string& bgFile,
                   const std::string& itemFile);
        ~HudCounter();

        void Update(float dt) {}

        void RhythmUpdate() {}
        void Render(Common::Layer layer) const;

        Sprite *bg, *counter;
        Rect boxbg;
        Vec2 offset1;
        Vec2 offset2;
};

#endif
