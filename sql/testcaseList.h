#ifndef TESTCASELIST_H
#define TESTCASELIST_H

#include <QStringList>


class TestCaseList
{
public:
    QStringList id{};
    QStringList name{};
    QStringList creator{};
    QStringList confirm{};

    void clearList() {
        id.clear();
        name.clear();
        creator.clear();
        confirm.clear();
    }

};

#endif // TESTCASELIST_H
