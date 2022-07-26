#ifndef TESTCASETABLESQL_H
#define TESTCASETABLESQL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>

#include "testcaseList.h"

class TestCaseTableSQL : public QObject
{
    Q_OBJECT
public:
    explicit TestCaseTableSQL(QObject *parent = nullptr);

private:
    QSqlQuery query{};
    TestCaseList testCaseList;

public slots:
    void getAllRecord();
    void insertNewRecord(const QString name, int userId);
    void updateExistRecord(int index, const QString name);
    void confirmTestCase(int index, int userId);
    void removeRecord(int index);

signals:
    void sendTestCases(TestCaseList);
    void sendError(QString);

};

#endif // TESTCASETABLESQL_H
