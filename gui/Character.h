#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include "lib/GameClient.h"

namespace Ui {
    class Character;
}

class Character : public QWidget
{
    Q_OBJECT

public:
    explicit Character(GameClient*, QWidget *parent = 0);
    ~Character();

private slots:
    void rspCharacterInfo(QVariantMap);
    void rspCharacterItems(QVariantList);
    void slotDress();
    void slotUndress();

private:
    Ui::Character *ui;
    GameClient* _gc;
};

#endif // CHARACTER_H
