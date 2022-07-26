#include "sequencewindowsql.h"
#include "ui_sequencewindowsql.h"


SequenceWindowSQL::SequenceWindowSQL(QWidget *parent, bool newRecord, int index, const QString sequence)
    : QDialog(parent)
    , ui(new Ui::SequenceWindowSQL)
    ,newRecord_(newRecord)
    , index_(index)
    , sqlSequence_(new SequenceTableSql)
{
    ui->setupUi(this);

    if(index != 0) {
        ui->lineEditName->setText(sequence);
    }
    connect(ui->pushButtonConfirm, &QPushButton::clicked, this, &SequenceWindowSQL::execSqlCommand);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &SequenceWindowSQL::windowClosed);

    connect(sqlSequence_, &SequenceTableSql::sendError, this, &SequenceWindowSQL::sendError);
}

SequenceWindowSQL::~SequenceWindowSQL() {
    delete ui;
}

void SequenceWindowSQL::execSqlCommand() {
    if(newRecord_) {
        sqlSequence_->insertNewRecord(ui->lineEditName->text());
    } else {
        sqlSequence_->updateExistRecord(index_, ui->lineEditName->text());
    }
    emit windowClosed();
}

void SequenceWindowSQL::closeEvent(QCloseEvent* event ) {
    emit windowClosed();
    event->accept();
}
