#ifndef SCENARIOSLIST_H
#define SCENARIOSLIST_H

#include <QStringList>


class ScenarioList
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

#endif // SCENARIOSLIST_H
