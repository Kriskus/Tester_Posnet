#include "sequencetablesql.h"

#include <QVariant>
#include <QSqlError>

SequenceTableSql::SequenceTableSql(QObject *parent)
    : QObject{parent}
{

}

void SequenceTableSql::getAllRecord() {
    seq.clearSequenceLists();
    query.exec("SELECT * FROM `Tester_db`.Sekwencje ORDER by sekwencja ASC;");
    while(query.next()) {
        seq.id.append(query.value(0).toString());
        seq.sequences.append(query.value(1).toString());
    }
    emit sendSequences(seq);
}

void SequenceTableSql::insertNewRecord(const QString sequence) {
    query.prepare("INSERT INTO `Tester_db`.`Sekwencje` (`sekwencja`) VALUES (:sequence);");
    query.bindValue(":sequence", sequence);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}

void SequenceTableSql::updateExistRecord(int index, const QString sequence) {
    query.prepare("UPDATE `Tester_db`.`Sekwencje` SET `sekwencja` = :sequence WHERE `id_sekwencji` = :index;");
    query.bindValue(":sequence", sequence);
    query.bindValue(":index", index);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}

void SequenceTableSql::removeRecord(int index) {
    query.prepare("DELETE FROM `Tester_db`.`Sekwencje` WHERE id_sekwencji = :index;");
    query.bindValue(":index", index);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}
