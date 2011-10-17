#include "lib/Mob.h"

Mob::Mob(QString title, int hp, int maxHp, int damage, int experience) :
    _title(title),
    _hp(hp),
    _maxHp(maxHp),
    _damage(damage),
    _experience(experience)
{
}

QString Mob::title()
{
    return _title;
}

int Mob::hp()
{
    return _hp;
}

int Mob::maxHp()
{
    return _maxHp;
}

int Mob::damage()
{
    return _damage;
}

int Mob::experience()
{
    return _experience;
}
