#ifndef TALK_H
#define TALK_H

#include <QWidget>
#include <QListWidgetItem>
#include "lib/GameClient.h"
#include "lib/Npc.h"

namespace Ui {
    class Talk;
}

class Talk : public QWidget
{
    Q_OBJECT

public:
    explicit Talk(GameClient*, Npc*, QWidget *parent = 0);
    ~Talk();

private slots:
    void changeQuest(QListWidgetItem*);
    void getQuest();

private:
    GameClient* _gc;
    Ui::Talk *ui;
    Npc* _npc;
};

#endif // TALK_H
