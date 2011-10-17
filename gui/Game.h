#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QList>
#include "lib/GameClient.h"

#define HERO_SIZE_X 30
#define HERO_SIZE_Y 30
#define TYPE_NPC 1
#define TYPE_MOB 2

namespace Ui {
    class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(GameClient*, QWidget *parent = 0);
    ~Game();

public slots:
    void rspCharacterInfo(QVariantMap);

private slots:
    void slotMoveHero();
    void slotMoveHeroLeft();
    void slotMoveHeroUp();
    void slotMoveHeroDown();
    void slotMoveHeroRight();
    void rspMove(QVariantMap);
    void rspCellContent(QVariantMap);
    void slotTalk();
    void reqQuests();
    void rspQuests(QVariantList);
    void slotCharacter();
    void slotTrade();

signals:
    void moveHero();

private:
    Ui::Game *ui;
    GameClient* _gc;
    QGraphicsScene* mapScene;
    QGraphicsPixmapItem* hero;
    QList<int> heroMovings;
    bool heroIsMoving;
    QVariantMap userInfo;
};

#endif // MAINWIDGET_H
