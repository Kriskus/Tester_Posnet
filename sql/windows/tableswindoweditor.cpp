#include "tableswindoweditor.h"
#include "ui_tableswindoweditor.h"

TablesWindowEditor::TablesWindowEditor(QWidget *parent, int tableSql, bool newRecord, int index, const QString name) :
    QDialog(parent),
    ui(new Ui::TablesWindowEditor)
  , newRecord_(newRecord)
  , index_(index)
  , sqlSequence_(new SequenceTableSql)
  , sqlScenario_(new ScenarioTableSQL)
  , sqlTestCase_(new TestCaseTableSQL)
{
    ui->setupUi(this);

    if(index != 0) {
        ui->lineEditName->setText(name);
    }
    connect(ui->pushButtonConfirm, &QPushButton::clicked, this, &TablesWindowEditor::execSqlCommand);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &TablesWindowEditor::windowClosed);

    connect(sqlSequence_, &SequenceTableSql::sendError, this, &TablesWindowEditor::sendError);
}

TablesWindowEditor::~TablesWindowEditor() {
    delete ui;
}

void TablesWindowEditor::execSqlCommand() {
    if(newRecord_) {
        sqlSequence_->insertNewRecord(ui->lineEditName->text());
    } else {
        sqlSequence_->updateExistRecord(index_, ui->lineEditName->text());
    }
    emit windowClosed();
}

void TablesWindowEditor::closeEvent(QCloseEvent *event) {
    emit windowClosed();
    event->accept();
}
