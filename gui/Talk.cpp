#include <QDebug>
#include "gui/Talk.h"
#include "ui_Talk.h"
#include "lib/Quest.h"

Talk::Talk(GameClient* gc, Npc* npc, QWidget *parent) :
    _gc(gc),
    _npc(npc),
    QWidget(parent),
    ui(new Ui::Talk)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem*)),
            SLOT(changeQuest(QListWidgetItem*)));
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(getQuest()));

    foreach (Quest* quest, npc->quests()) {
        QListWidgetItem* questItem = new QListWidgetItem(ui->listWidget);

        questItem->setText(quest->title());
        questItem->setData(Qt::UserRole, qVariantFromValue((void*)quest));

        ui->listWidget->addItem(questItem);
    }
}

Talk::~Talk()
{
    delete ui;
}

void Talk::changeQuest(QListWidgetItem* item)
{
    Quest* quest = (Quest*)item->data(Qt::UserRole).value<void*>();
    ui->textEdit->setText(quest->text());
}

void Talk::getQuest()
{
    if (!ui->listWidget->currentItem())
        return;

    Quest* quest = (Quest*)ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();

    QVariantMap args;
    args["idNpc"] = _npc->id();
    args["idQuest"] = quest->id();

    _gc->sendToServer("reqGetQuest", args);
}
