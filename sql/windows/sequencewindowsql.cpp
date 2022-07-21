#include "sequencewindowsql.h"
#include "ui_sequencewindowsql.h"


SequenceWindowSQL::SequenceWindowSQL(QWidget *parent, bool newRecord, int index, const QString sequence)
    : QDialog(parent)
    , ui(new Ui::SequenceWindowSQL)
    ,newRecord_(newRecord)
{
    ui->setupUi(this);

    if(index != 0) {
        ui->labelIdNumber->setText(QString::number(index));
        ui->lineEditName->setText(sequence);
    }
    connect(ui->pushButtonConfirm, &QPushButton::clicked, this, &SequenceWindowSQL::execSqlCommand);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &SequenceWindowSQL::windowClosed);

}

SequenceWindowSQL::~SequenceWindowSQL()
{
    delete ui;
}

void SequenceWindowSQL::execSqlCommand()
{
    if(newRecord_) {
        sqlSequence_.insertNewRecord(ui->lineEditName->text());
    } else {
        sqlSequence_.updateExistRecord(ui->labelIdNumber->text().toInt(), ui->lineEditName->text());
    }
    emit confirmed();
    emit windowClosed();
}

void SequenceWindowSQL::closeEvent(QCloseEvent* event ) {
    emit windowClosed();
    event->accept();
}
