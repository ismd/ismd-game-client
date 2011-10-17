#include "lib/Quest.h"

Quest::Quest(int id, QString title, QString text) :
    _id(id),
    _title(title),
    _text(text)
{
}

int Quest::id()
{
    return _id;
}

QString Quest::title()
{
    return _title;
}

QString Quest::text()
{
    return _text;
}
