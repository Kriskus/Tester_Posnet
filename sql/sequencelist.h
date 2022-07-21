#ifndef SEQUENCELIST_H
#define SEQUENCELIST_H

#include <QStringList>


struct SequenceList
{
    QStringList id{};
    QStringList sequences{};

    void clearSequenceLists() {
        sequences.clear();
        id.clear();
    }
};

#endif // SEQUENCELIST_H
