#ifndef SEQUENCEWINDOWSQL_H
#define SEQUENCEWINDOWSQL_H

#include <QCloseEvent>
#include <QDialog>

#include "sql/sequencetablesql.h"

namespace Ui {
class SequenceWindowSQL;
}

class SequenceWindowSQL : public QDialog
{
    Q_OBJECT

public:
    explicit SequenceWindowSQL(QWidget *parent = nullptr, bool newRecord = true, int index = 0, const QString sequence = QString());
    ~SequenceWindowSQL();

private:
    Ui::SequenceWindowSQL *ui;
    SequenceTableSql *sqlSequence_;
    bool newRecord_{true};
    int index_{0};

    void execSqlCommand();

    void closeEvent(QCloseEvent *event);

signals:
    void windowClosed();
    void sendError(QString);
};

#endif // SEQUENCEWINDOWSQL_H
