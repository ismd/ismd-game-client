#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QList>
#include "lib/Quest.h"
#include "lib/Item.h"

class Npc
{
public:
    Npc(int id, QString name);
    int id();
    void appendQuest(Quest*);
    void appendItem(Item*);
    QList<Quest*> quests();
    QList<Item*> items();

private:
    int _id;
    QString _name;
    QList<Quest*> _quests;
    QList<Item*> _items;
};

#endif // NPC_H
