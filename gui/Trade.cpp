#include "gui/Trade.h"
#include "ui_Trade.h"

Trade::Trade(GameClient* gc, Npc* npc, QWidget *parent) :
    _gc(gc),
    _npc(npc),
    QWidget(parent),
    ui(new Ui::Trade)
{
    ui->setupUi(this);

    foreach (Item* item, npc->items()) {
        QListWidgetItem* wItem = new QListWidgetItem(item->title() + " (" + QString::number(item->price()) +
                                                     trUtf8(" монет)"), ui->lItems);

        QString tooltip = trUtf8("Тип: ") + QString::number(item->idType()) +
                          (item->description() != "" ? trUtf8("\nОписание: ") +
                          item->description() : "");
        wItem->setToolTip(tooltip);

        ui->lItems->addItem(wItem);
    }
}

Trade::~Trade()
{
    delete ui;
}
