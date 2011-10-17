#ifndef MOB_H
#define MOB_H

#include <QString>

class Mob
{
public:
    Mob(QString title, int hp, int maxHp, int damage, int experience);
    QString title();
    int hp();
    int maxHp();
    int damage();
    int experience();

private:
    QString _title;
    int _hp;
    int _maxHp;
    int _damage;
    int _experience;
};

#endif // MOB_H
