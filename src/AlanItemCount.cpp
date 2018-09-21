#include "AlanItemCount.h"
#include "Common.h"

AlanItemCount::AlanItemCount(GameObject& associated) : Component(associated) {
    itemCount.emplace(Common::ItemType::GOLD, rand() % 5);
    itemCountItem.emplace(Common::ItemType::GOLD,
                          new GameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::GOLD]->box.x = 950;
    itemCountItem[Common::ItemType::GOLD]->box.y = 115;
    itemCountItem[Common::ItemType::GOLD]->world_reference = false;
    Sprite* sprite = new Sprite(*itemCountItem[Common::ItemType::GOLD],
                                "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::GOLD]->AddComponent(sprite);
    itemCountItem[Common::ItemType::GOLD]->AddComponent(new Item(
        *itemCountItem[Common::ItemType::GOLD],
        itemCountItem[Common::ItemType::GOLD]->box.Center(),
        Vec2(itemCountItem[Common::ItemType::GOLD]->box.Center().x + 20,
             itemCountItem[Common::ItemType::GOLD]->box.Center().y + 5)));
    std::cout << "GOLD COUNT = " << itemCount[Common::ItemType::GOLD]
              << std::endl;
    sprite->SetFrame(itemCount[Common::ItemType::GOLD]);

    itemCount.emplace(Common::ItemType::DIAMOND, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::DIAMOND,
                          new GameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::DIAMOND]->box.x = 950;
    itemCountItem[Common::ItemType::DIAMOND]->box.y = 263;
    itemCountItem[Common::ItemType::DIAMOND]->world_reference = false;
    sprite = new Sprite(*itemCountItem[Common::ItemType::DIAMOND],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::DIAMOND]->AddComponent(sprite);
    itemCountItem[Common::ItemType::DIAMOND]->AddComponent(new Item(
        *itemCountItem[Common::ItemType::DIAMOND],
        itemCountItem[Common::ItemType::DIAMOND]->box.Center(),
        Vec2(itemCountItem[Common::ItemType::DIAMOND]->box.Center().x + 20,
             itemCountItem[Common::ItemType::DIAMOND]->box.Center().y + 5)));
    sprite->SetFrame(itemCount[Common::ItemType::DIAMOND]);

    itemCount.emplace(Common::ItemType::PETROLEUM, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::PETROLEUM,
                          new GameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::PETROLEUM]->box.x = 950;
    itemCountItem[Common::ItemType::PETROLEUM]->box.y = 415;
    itemCountItem[Common::ItemType::PETROLEUM]->world_reference = false;
    sprite = new Sprite(*itemCountItem[Common::ItemType::PETROLEUM],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::PETROLEUM]->AddComponent(sprite);
    itemCountItem[Common::ItemType::PETROLEUM]->AddComponent(new Item(
        *itemCountItem[Common::ItemType::PETROLEUM],
        itemCountItem[Common::ItemType::PETROLEUM]->box.Center(),
        Vec2(itemCountItem[Common::ItemType::PETROLEUM]->box.Center().x + 20,
             itemCountItem[Common::ItemType::PETROLEUM]->box.Center().y + 5)));
    sprite->SetFrame(itemCount[Common::ItemType::PETROLEUM]);
}

void AlanItemCount::render(Common::Layer layer) const {
    for (auto item : itemCountItem) {
        item.second->box.SetCenter(item.second->GetComponent<Item*>()->center);

        if (!itemCount.at(item.first)) {
            item.second->GetComponent<Item*>()->bg->SetColor(0, 255, 0);
        }

        item.second->GetComponent<Item*>()->bg->render(layer);

        item.second->GetComponent<Item*>()->bg->SetColor(255, 255, 255);

        item.second->box.SetCenter(
            item.second->GetComponent<Item*>()->numberCenter);
        item.second->RenderOrder(layer);
    }
}
