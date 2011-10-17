#ifndef QUEST_H
#define QUEST_H

#include <QString>

class Quest
{
public:
    Quest(int id, QString title, QString text);
    int id();
    QString title();
    QString text();

private:
    int _id;
    QString _title;
    QString _text;
};

#endif // QUEST_H
