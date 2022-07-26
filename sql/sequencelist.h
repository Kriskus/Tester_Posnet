#ifndef SEQUENCELIST_H
#define SEQUENCELIST_H

#include <QStringList>


struct SequenceList
{
    QStringList id{};
    QStringList name{};

    void clearList() {
        id.clear();
        name.clear();
    }
};

#endif // SEQUENCELIST_H
