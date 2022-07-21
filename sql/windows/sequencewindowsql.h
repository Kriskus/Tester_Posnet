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
    SequenceTableSql sqlSequence_;
    bool newRecord_{true};

    void execSqlCommand();

    void closeEvent(QCloseEvent *event);

signals:
    void windowClosed();
    void confirmed();
};

#endif // SEQUENCEWINDOWSQL_H
