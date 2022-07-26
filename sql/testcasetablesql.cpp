#include "testcasetablesql.h"

#include <QVariant>

TestCaseTableSQL::TestCaseTableSQL(QObject *parent)
    : QObject{parent} {

}

void TestCaseTableSQL::getAllRecord() {
    testCaseList.clearList();
    query.exec("SELECT * FROM `Tester_db`.Przypadki_Testowe ORDER by nazwa_przypadku ASC;");
    while(query.next()) {
        testCaseList.id.append(query.value(0).toString());
        testCaseList.name.append(query.value(1).toString());
    }
    emit sendTestCases(testCaseList);
}

void TestCaseTableSQL::insertNewRecord(const QString name, int userId) {
    query.prepare("INSERT INTO `Tester_db`.`Przypadki_Testowe` (`id_scenariusza`, `nazwa_przypadku`, `id_uzytkownika_stworzenie`) VALUES (:idScenario, :name, :userId);");
    query.bindValue(":name", name);
    query.bindValue(":userId", userId);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}

void TestCaseTableSQL::updateExistRecord(int index, const QString name) {
    query.prepare("UPDATE `Tester_db`.`Przypadki_Testowe` SET `nazwa_przypadku` = :name WHERE `id_sekwencji` = :index;");
    query.bindValue(":name", name);
    query.bindValue(":index", index);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}

void TestCaseTableSQL::confirmTestCase(int index, int userId) {
    query.prepare("UPDATE `Tester_db`.`Przypadki_Testowe` SET `id_uzytkownika_potwierdzenie` = :userId WHERE `id_sekwencji` = :index;");
    query.bindValue(":userId", userId);
    query.bindValue(":index", index);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}

void TestCaseTableSQL::removeRecord(int index) {
    query.prepare("DELETE FROM `Tester_db`.`Przypadki_Testowe` WHERE id_sekwencji = :index;");
    query.bindValue(":index", index);
    query.exec();
    if(query.lastError().text() != "") {
        emit sendError(query.lastError().text());
    }
}
