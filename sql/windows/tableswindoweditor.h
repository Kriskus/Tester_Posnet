#ifndef TABLESWINDOWEDITOR_H
#define TABLESWINDOWEDITOR_H

#include <QCloseEvent>
#include <QDialog>

#include "sql/sequencetablesql.h"
#include "sql/scenariotablesql.h"
#include "sql/testcasetablesql.h"

namespace Ui {
class TablesWindowEditor;
}

class TablesWindowEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TablesWindowEditor(QWidget *parent = nullptr, int tableSql = 0, bool newRecord = true, int index = 0, const QString name = QString());
    ~TablesWindowEditor();

private:
    Ui::TablesWindowEditor *ui;
    SequenceTableSql *sqlSequence_;
    ScenarioTableSQL *sqlScenario_;
    TestCaseTableSQL *sqlTestCase_;
    bool newRecord_{true};
    int index_{0};

    void execSqlCommand();

    void closeEvent(QCloseEvent *event);

signals:
    void windowClosed();
    void sendError(QString);
};

#endif // TABLESWINDOWEDITOR_H
