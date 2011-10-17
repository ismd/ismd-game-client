#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    Item(int id, QString title, int idType, int price, QString description);
    int id();
    QString title();
    int idType();
    int price();
    QString description();

private:
    int _id;
    QString _title;
    int _idType;
    int _price;
    QString _description;
};

#endif // ITEM_H
