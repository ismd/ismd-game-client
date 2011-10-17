#include <QtTest>
#include "Game.h"
#include "ui_Game.h"
#include "gui/Talk.h"
#include "lib/Npc.h"
#include "lib/Quest.h"
#include "lib/Mob.h"
#include "gui/Character.h"
#include "lib/Item.h"
#include "gui/Trade.h"

Game::Game(GameClient* gc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    _gc(gc),
    heroIsMoving(false)
{
    ui->setupUi(this);

    mapScene = new QGraphicsScene;
    ui->gvMap->setScene(mapScene);

    mapScene->addPixmap(QPixmap(":/images/map.png"));
    hero = mapScene->addPixmap(QPixmap(":/images/hero.png"));

    connect(this, SIGNAL(moveHero()), SLOT(slotMoveHero()));
    connect(_gc, SIGNAL(rspMove(QVariantMap)), SLOT(rspMove(QVariantMap)));
    connect(_gc, SIGNAL(rspCellContent(QVariantMap)), SLOT(rspCellContent(QVariantMap)));
    connect(_gc, SIGNAL(rspQuests(QVariantList)), SLOT(rspQuests(QVariantList)));
    connect(ui->bLeft, SIGNAL(clicked()), SLOT(slotMoveHeroLeft()));
    connect(ui->bUp, SIGNAL(clicked()), SLOT(slotMoveHeroUp()));
    connect(ui->bDown, SIGNAL(clicked()), SLOT(slotMoveHeroDown()));
    connect(ui->bRight, SIGNAL(clicked()), SLOT(slotMoveHeroRight()));
    connect(ui->bTalk, SIGNAL(clicked()), SLOT(slotTalk()));
    connect(ui->bQuests, SIGNAL(clicked()), SLOT(reqQuests()));
    connect(ui->bCharacter, SIGNAL(clicked()), SLOT(slotCharacter()));
    connect(ui->bTrade, SIGNAL(clicked()), SLOT(slotTrade()));

    _gc->sendToServer("reqCellContent", QVariant());
}

void Game::slotMoveHero()
{
    heroIsMoving = true;

    while (!heroMovings.isEmpty()) {
        int direction = heroMovings.first();
        heroMovings.removeFirst();

        int dx = 0;
        int dy = 0;

        switch (direction) {
        case 0:
            dx = -1;
            break;

        case 1:
            dy = -1;
            break;
        case 2:
            dy = 1;
            break;

        case 3:
            dx = 1;
            break;

        default:
            qDebug() << "Error: unknown direction";
            return;
            break;
        }

        QVariantMap newCoordinates;
        newCoordinates["dx"] = dx;
        newCoordinates["dy"] = dy;

        _gc->sendToServer("reqMove", newCoordinates);
    }

    heroIsMoving = false;
}

void Game::rspMove(QVariantMap args)
{
    int dx = args["dx"].toInt();
    int dy = args["dy"].toInt();
    int size = (dx == 0 ? (dy == 0 ? 0 : HERO_SIZE_Y) : HERO_SIZE_X);

    for (int i = 0; i < size; i++) {
        hero->moveBy(dx, dy);
        ui->gvMap->centerOn(hero);
        QTest::qWait(50);

        if (i == (int)(size / 2))
            ui->lCellContent->clear();
    }
}

void Game::slotMoveHeroLeft()
{
    heroMovings.append(0);

    if (!heroIsMoving)
        emit moveHero();
}

void Game::slotMoveHeroUp()
{
    heroMovings.append(1);

    if (!heroIsMoving)
        emit moveHero();
}

void Game::slotMoveHeroDown()
{
    heroMovings.append(2);

    if (!heroIsMoving)
        emit moveHero();
}

void Game::slotMoveHeroRight()
{
    heroMovings.append(3);

    if (!heroIsMoving)
        emit moveHero();
}

Game::~Game()
{
    delete ui;
}

void Game::rspCharacterInfo(QVariantMap info)
{
    userInfo = info;

    ui->labelName->setText(userInfo["name"].toString());
    ui->labelLevel->setText(userInfo["level"].toString());
    ui->labelMoney->setText(userInfo["money"].toString());

    hero->setX(userInfo["coordinateX"].toInt() * HERO_SIZE_X);
    hero->setY(userInfo["coordinateY"].toInt() * HERO_SIZE_Y);
    ui->gvMap->centerOn(hero);
}

void Game::rspCellContent(QVariantMap args)
{
    ui->lCellContent->clear();

    QVariantList npcs = args["npcs"].toList();
    foreach (QVariant npct, npcs) {
        QVariantMap npc = npct.toMap();
        int id = npc["id"].toInt();
        QString name = npc["name"].toString();
        QVariantList quests = npc["quests"].toList();
        QVariantList items = npc["items"].toList();

        Npc* npcCurr = new Npc(id, name);

        foreach (QVariant quest, quests) {
            QVariantMap q = quest.toMap();

            int idQuest = q["id"].toInt();
            QString questTitle = q["title"].toString();
            QString questText = q["text"].toString();

            npcCurr->appendQuest(new Quest(idQuest, questTitle, questText));
        }

        foreach (QVariant item, items) {
            QVariantMap i = item.toMap();

            int idItem = i["id"].toInt();
            QString title = i["title"].toString();
            int idType = i["idType"].toInt();
            int price = i["price"].toInt();
            QString description = i["description"].toString();

            npcCurr->appendItem(new Item(idItem, title, idType, price, description));
        }

        QListWidgetItem* item = new QListWidgetItem(ui->lCellContent);
        item->setIcon(QIcon(":/images/hero.png"));
        item->setToolTip(name);
        item->setText(name);
        item->setData(Qt::UserRole, TYPE_NPC);
        item->setData(Qt::UserRole + 1, qVariantFromValue((void*)npcCurr));
        ui->lCellContent->addItem(item);
    }

    QVariantList mobs = args["mobs"].toList();
    foreach (QVariant mobv, mobs) {
        QVariantMap mob = mobv.toMap();
        QString title = mob["title"].toString();
        int hp = mob["hp"].toInt();
        int maxHp = mob["hp"].toInt();
        int damage = mob["damage"].toInt();
        int experience = mob["experience"].toInt();

        Mob* mobCurr = new Mob(title, hp, maxHp, damage, experience);

        QListWidgetItem* item = new QListWidgetItem(ui->lCellContent);
        item->setIcon(QIcon(":/images/hero.png"));

        QString fullInfo = trUtf8("Здоровье: ") + QString::number(hp) + "\n" +
                trUtf8("Макс. здоровье: ") + QString::number(maxHp) + "\n" + trUtf8("Урон: ") +
                QString::number(damage);
        item->setToolTip(fullInfo);
        item->setText(title);
        item->setData(Qt::UserRole, TYPE_MOB);
        item->setData(Qt::UserRole + 1, qVariantFromValue((void*)mobCurr));
        ui->lCellContent->addItem(item);
    }
}

void Game::slotTalk()
{
    if (!ui->lCellContent->currentItem())
        return;

    int currentItemType = (int)ui->lCellContent->currentItem()->data(Qt::UserRole).value<int>();
    if (currentItemType != TYPE_NPC)
        return;

    Npc* currNpc = (Npc*)ui->lCellContent->currentItem()->data(Qt::UserRole + 1).value<void*>();

    Talk* talk = new Talk(_gc, currNpc);
    talk->show();
}

void Game::reqQuests()
{
    _gc->sendToServer("reqQuests", QVariant());
}

void Game::rspQuests(QVariantList quests)
{
    QListWidget* questsWindow = new QListWidget;

    foreach (QVariant questV, quests) {
        QVariantMap quest = questV.toMap();

        questsWindow->addItem(quest["title"].toString());
    }

    questsWindow->show();
}

void Game::slotCharacter()
{
    Character* character = new Character(_gc);
    character->show();
}

void Game::slotTrade()
{
    if (!ui->lCellContent->currentItem())
        return;

    int currentItemType = (int)ui->lCellContent->currentItem()->data(Qt::UserRole).value<int>();
    if (currentItemType != TYPE_NPC)
        return;

    Npc* currNpc = (Npc*)ui->lCellContent->currentItem()->data(Qt::UserRole + 1).value<void*>();

    Trade* trade = new Trade(_gc, currNpc);
    trade->show();
}
