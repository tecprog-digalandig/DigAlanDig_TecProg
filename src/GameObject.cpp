#include "GameObject.h"
#include "Sound.h"

bool GameObject::CanEnd() const {
    //    if (Sound* sound = (Sound*)GetComponent("Sound")) return
    //    sound->CanEnd(); return false;
    return true;
}

GameObject::~GameObject() {
    for (Component* component : components) delete (component);

    components.clear();
}

void GameObject::Update(float dt) {
    // TODO: parallel_for, opemmp fop_each
    for (Component* component : components) component->Update(dt);
}

void GameObject::Render() {
    for (Component* component : components) component->Render();
}

void GameObject::NotifyCollision(std::shared_ptr<GameObject> other) {
    for (Component* component : components) component->NotifyCollision(other);
}

void GameObject::RemoveComponent(Component* cpt) {
    // CHECK: delete cpt?
    components.erase(std::remove(components.begin(), components.end(), cpt),
                     components.end());
}

Component* GameObject::GetComponent(const std::string& type) const {
    for (Component* component : components)
        if (component->Is(type)) return component;

    return nullptr;
}

void GameObject::AddComponent(Component* cpt) { components.emplace_back(cpt); }

void GameObject::CopyPosition(const GameObject& go) {
    box = go.box;
    worldReference = go.worldReference;
    fromPlayer = go.fromPlayer;
    angleDeg = go.angleDeg;
}

void GameObject::Start() {
    if (started) return;
    for (auto c : components) c->Start();

    started = true;
}
