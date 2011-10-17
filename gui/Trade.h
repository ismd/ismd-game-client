#ifndef TRADE_H
#define TRADE_H

#include <QWidget>
#include "lib/GameClient.h"
#include "lib/Npc.h"

namespace Ui {
    class Trade;
}

class Trade : public QWidget
{
    Q_OBJECT

public:
    explicit Trade(GameClient*, Npc*, QWidget *parent = 0);
    ~Trade();

private:
    Ui::Trade *ui;
    GameClient* _gc;
    Npc* _npc;
};

#endif // TRADE_H
