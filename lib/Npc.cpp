#include "lib/Npc.h"

Npc::Npc(int id, QString name)
{
    _id = id;
    _name = name;
}

int Npc::id()
{
    return _id;
}

void Npc::appendQuest(Quest* quest)
{
    _quests.append(quest);
}

void Npc::appendItem(Item* item)
{
    _items.append(item);
}

QList<Quest*> Npc::quests()
{
    return _quests;
}

QList<Item*> Npc::items()
{
    return _items;
}
