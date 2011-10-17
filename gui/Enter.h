#ifndef ENTER_H
#define ENTER_H

#include <QWidget>
#include "lib/GameClient.h"
#include "Game.h"

namespace Ui {
    class Enter;
}

class Enter : public QWidget
{
    Q_OBJECT

public:
    explicit Enter(QWidget *parent = 0);
    ~Enter();

private slots:
    void runGame();
    void slotAuth(bool);
    void slotConnectionSucceeded();
    void slotConnectionError();
    void openGameWindow();

private:
    Ui::Enter *ui;
    GameClient* gc;
    Game* gw;
};

#endif // ENTER_H
