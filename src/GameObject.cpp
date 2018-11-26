#include "GameObject.h"
#include "Sound.h"

bool GameObject::CanEnd() const { return true; }

GameObject::~GameObject() {
    for (Component* component : components) delete (component);

    components.clear();
    tmp = box;
}

void GameObject::update(float dt) {
    static float sum;
    sum += dt;
    for (Component* component : components) component->update(dt);
    if (move) {
        box.pos = tmp.pos + Vec2(0, 1) * sin(sum) * 30;
    }
}

void GameObject::rhythmUpdate() {
    for (Component* component : components) component->rhythmUpdate();
}

void GameObject::RhythmReset() {
    for (Component* component : components) component->RhythmReset();
}

void GameObject::RenderOrder(Common::Layer layer) const {
    if (!(this->layer & layer)) return;

    for (Component* component : components) component->render(layer);
}

void GameObject::RemoveComponent(Component* cpt) {
    components.erase(std::remove(components.begin(), components.end(), cpt),
                     components.end());
}

void GameObject::AddComponent(Component* cpt) { components.emplace_back(cpt); }

void GameObject::CopyPosition(const GameObject& go) {
    box = go.box;
    world_reference = go.world_reference;
    fromPlayer = go.fromPlayer;
    angleDeg = go.angleDeg;
}

void GameObject::start() {
    if (started) return;
    for (auto c : components) c->start();

    started = true;
}
