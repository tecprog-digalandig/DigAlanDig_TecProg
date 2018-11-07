#include "GameObject.h"
#include "Sound.h"

bool GameObject::canEnd() const { return true; }

GameObject::~GameObject()
{
    for (Component* component : components) delete (component);

    components.clear();
    tmp = box;
}

void GameObject::Update(float delta_time) {
    static float sum;
    sum += delta_time;
    for (Component* component : components) component->Update(delta_time);
    if (move) {
        box.pos = tmp.pos + Vec2(0, 1) * sin(sum) * 30;
    }
}

void GameObject::rhythmUpdate() {
    for (Component* component : components) component->rhythmUpdate();
}

void GameObject::RhythmReset()
{
    for (Component* component : components) component->RhythmReset();
}

void GameObject::renderOrder(Common::Layer layer) const {
    if (!(this->layer & layer)) return;

    for (Component* component : components) component->render(layer);
}

void GameObject::RemoveComponent(Component* cpt)
{
    components.erase(std::remove(components.begin(), components.end(), cpt),
    components.end());
}

void GameObject::addComponent(Component* cpt) { components.emplace_back(cpt); }

void GameObject::CopyPosition(const GameObject& go)
{
    box = go.box;
    world_reference = go.world_reference;
    from_player = go.from_player;
    angle_deg = go.angle_deg;
}

void GameObject::Start()
{
    if (started) return;
    for (auto c : components) c->Start();

    started = true;
}
