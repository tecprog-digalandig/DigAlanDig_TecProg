#include "AlanItemCount.h"
#include "Common.h"

AlanItemCount::AlanItemCount(GameObject& associated) : Component(associated) 
{
    item_count.emplace(Common::ItemType::gold, rand() % 5);
    item_count_item.emplace(Common::ItemType::gold,
                          new GameObject(Common::Layer::HUD));
<<<<<<< HEAD
    item_count_item[Common::ItemType::gold]->box.x = 950;
    item_count_item[Common::ItemType::gold]->box.y = 115;
    item_count_item[Common::ItemType::gold]->world_reference = false;
    Sprite* sprite =new Sprite(*item_count_item[Common::ItemType::gold],
=======
    itemCountItem[Common::ItemType::GOLD]->box.x = 950;
    itemCountItem[Common::ItemType::GOLD]->box.y = 115;
    itemCountItem[Common::ItemType::GOLD]->world_reference = false;
    Sprite* sprite = new Sprite(*itemCountItem[Common::ItemType::GOLD],
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
                                "assets/hud/numbers.png", 10, -2);
    item_count_item[Common::ItemType::gold]->addComponent(sprite);
    item_count_item[Common::ItemType::gold]->addComponent(new Item(
        *item_count_item[Common::ItemType::gold],
        item_count_item[Common::ItemType::gold]->box.Center(),
        Vec2(item_count_item[Common::ItemType::gold]->box.Center().x + 20,
             item_count_item[Common::ItemType::gold]->box.Center().y + 5)));
    std::cout << "gold COUNT = " << item_count[Common::ItemType::gold]
              << std::endl;
    sprite->setFrame(item_count[Common::ItemType::gold]);

    item_count.emplace(Common::ItemType::diamond, rand() % 5 + 4);
    item_count_item.emplace(Common::ItemType::diamond,
                          new GameObject(Common::Layer::HUD));
<<<<<<< HEAD
    item_count_item[Common::ItemType::diamond]->box.x = 950;
    item_count_item[Common::ItemType::diamond]->box.y = 263;
    item_count_item[Common::ItemType::diamond]->world_reference = false;
    sprite =new Sprite(*item_count_item[Common::ItemType::diamond],
=======
    itemCountItem[Common::ItemType::DIAMOND]->box.x = 950;
    itemCountItem[Common::ItemType::DIAMOND]->box.y = 263;
    itemCountItem[Common::ItemType::DIAMOND]->world_reference = false;
    sprite = new Sprite(*itemCountItem[Common::ItemType::DIAMOND],
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
                        "assets/hud/numbers.png", 10, -2);
    item_count_item[Common::ItemType::diamond]->addComponent(sprite);
    item_count_item[Common::ItemType::diamond]->addComponent(new Item(
        *item_count_item[Common::ItemType::diamond],
        item_count_item[Common::ItemType::diamond]->box.Center(),
        Vec2(item_count_item[Common::ItemType::diamond]->box.Center().x + 20,
             item_count_item[Common::ItemType::diamond]->box.Center().y + 5)));
    sprite->setFrame(item_count[Common::ItemType::diamond]);

    item_count.emplace(Common::ItemType::petroleum, rand() % 5 + 4);
    item_count_item.emplace(Common::ItemType::petroleum,
                          new GameObject(Common::Layer::HUD));
<<<<<<< HEAD
    item_count_item[Common::ItemType::petroleum]->box.x = 950;
    item_count_item[Common::ItemType::petroleum]->box.y = 415;
    item_count_item[Common::ItemType::petroleum]->world_reference = false;
    sprite =new Sprite(*item_count_item[Common::ItemType::petroleum],
=======
    itemCountItem[Common::ItemType::PETROLEUM]->box.x = 950;
    itemCountItem[Common::ItemType::PETROLEUM]->box.y = 415;
    itemCountItem[Common::ItemType::PETROLEUM]->world_reference = false;
    sprite = new Sprite(*itemCountItem[Common::ItemType::PETROLEUM],
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
                        "assets/hud/numbers.png", 10, -2);
    item_count_item[Common::ItemType::petroleum]->addComponent(sprite);
    item_count_item[Common::ItemType::petroleum]->addComponent(new Item(
        *item_count_item[Common::ItemType::petroleum],
        item_count_item[Common::ItemType::petroleum]->box.Center(),
        Vec2(item_count_item[Common::ItemType::petroleum]->box.Center().x + 20,
             item_count_item[Common::ItemType::petroleum]->box.Center().y + 5)));
    sprite->setFrame(item_count[Common::ItemType::petroleum]);
}

void AlanItemCount::render(Common::Layer layer) const 
{
    for (auto item : item_count_item) 
    {
        item.second->box.setCenter(item.second->GetComponent<Item*>()->center);

        if (!item_count.at(item.first)) 
        {
            item.second->GetComponent<Item*>()->bg->setColor(0, 255, 0);
        }

        item.second->GetComponent<Item*>()->bg->render(layer);

        item.second->GetComponent<Item*>()->bg->setColor(255, 255, 255);

        item.second->box.setCenter(
            item.second->GetComponent<Item*>()->numberCenter);
        item.second->renderOrder(layer);
    }
}
