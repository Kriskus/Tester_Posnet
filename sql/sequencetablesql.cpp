#include "sequencetablesql.h"

#include <QVariant>

SequenceTableSql::SequenceTableSql(QObject *parent)
    : QObject{parent}
{

}

void SequenceTableSql::getAllRecord() {
    seq.clearSequenceLists();
    query.exec("SELECT * FROM Sekwencje ORDER by id_sekwencji");
    while(query.next()) {
        seq.id.append(query.value(0).toString());
        seq.sequences.append(query.value(1).toString());
    }
    emit sendSequences(seq);
}

void SequenceTableSql::insertNewRecord(const QString sequence) {
    query.prepare("INSERT INTO `Sekwencje` (`sekwencja`) VALUES (:sequence);");
    query.bindValue(":sequence", sequence);
    query.exec();
}

void SequenceTableSql::updateExistRecord(int index, const QString sequence) {
    query.prepare("UPDATE `Sekwencje` SET `sekwencja` = :sequence WHERE `id_sekwencji` = :index;");
    query.bindValue(":sequence", sequence);
    query.bindValue(":index", index);
    query.exec();
}

void SequenceTableSql::removeRecord(int index) {
    query.prepare("DELETE FROM `Tester_db`.`Sekwencje` WHERE id_sekwencji = :index;");
    query.bindValue(":index", index);
    query.exec();
}
