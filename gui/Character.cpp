#include "gui/Character.h"
#include "ui_Character.h"

Character::Character(GameClient* gc, QWidget *parent) :
    _gc(gc),
    QWidget(parent),
    ui(new Ui::Character)
{
    ui->setupUi(this);

    connect(_gc, SIGNAL(rspCharacterInfo(QVariantMap)), SLOT(rspCharacterInfo(QVariantMap)));
    connect(_gc, SIGNAL(rspCharacterItems(QVariantList)), SLOT(rspCharacterItems(QVariantList)));
    connect(ui->bDress, SIGNAL(clicked()), SLOT(slotDress()));
    connect(ui->bUndress, SIGNAL(clicked()), SLOT(slotUndress()));

    _gc->sendToServer("reqCharacterInfo", QVariant());
    _gc->sendToServer("reqCharacterItems", QVariant());
}

Character::~Character()
{
    delete ui;
}

void Character::rspCharacterInfo(QVariantMap info)
{
    ui->lName->setText(info["name"].toString());
    ui->lLevel->setText(info["level"].toString());
    ui->lMoney->setText(info["money"].toString());
}

void Character::rspCharacterItems(QVariantList items)
{
    foreach (QVariant item, items) {
        QVariantMap itemMap = item.toMap();
        QListWidgetItem* wItem = new QListWidgetItem(itemMap["title"].toString() + " (" +
                                                     itemMap["price"].toString() + trUtf8(" монет)"), ui->lItems);

        QString tooltip = trUtf8("Тип: ") + itemMap["idType"].toString() +
                          (itemMap["description"].toString() != "" ? trUtf8("\nОписание: ") +
                          itemMap["description"].toString() : "");
        wItem->setToolTip(tooltip);
        wItem->setData(Qt::UserRole, item.toMap());

        ui->lItems->addItem(wItem);
    }
}

void Character::slotDress()
{
    QVariantMap item = ui->lItems->currentItem()->data(Qt::UserRole).toMap();

    ui->lItemsOnCharacter->addItem(item["title"].toString());
}

void Character::slotUndress()
{

}
