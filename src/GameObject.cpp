#include "GameObject.h"
#include "Sound.h"

bool GameObject::canEnd() const { return true; }

GameObject::~GameObject()
{
    for (Component* component : components) delete (component);

    components.clear();
    tmp = box;
}

void GameObject::Update(float dt)
{
    static float sum;
    sum += dt;
    for (Component* component : components) component->Update(dt);
    if (move)
    {
        box.pos = tmp.pos + Vec2(0, 1) * sin(sum) * 30;
    }
}

void GameObject::RhythmUpdate()
{
    for (Component* component : components) component->RhythmUpdate();
}

void GameObject::RhythmReset()
{
    for (Component* component : components) component->RhythmReset();
}

void GameObject::RenderOrder(Common::Layer layer) const
{
    if (!(this->layer & layer)) return;

    for (Component* component : components) component->Render(layer);
}

void GameObject::RemoveComponent(Component* cpt)
{
    components.erase(std::remove(components.begin(), components.end(), cpt),
    components.end());
}

void GameObject::AddComponent(Component* cpt) { components.emplace_back(cpt); }

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
