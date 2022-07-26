#ifndef SEQUENCETABLESQL_H
#define SEQUENCETABLESQL_H

#include "SequenceList.h"

#include <QObject>
#include <QSqlQuery>

class SequenceTableSql : public QObject
{
    Q_OBJECT
public:
    explicit SequenceTableSql(QObject *parent = nullptr);

private:
    QSqlQuery query{};
    SequenceList seq;

public slots:
    void getAllRecord();
    void insertNewRecord(const QString sequence);
    void updateExistRecord(int index, const QString sequence);
    void removeRecord(int index);

signals:
    void sendSequences(SequenceList);
    void sendError(QString);
};

#endif // SEQUENCETABLESQL_H
