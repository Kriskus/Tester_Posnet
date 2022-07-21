#include "logscreen.h"
#include "ui_logscreen.h"
#include "mainwindow/mainwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

LogScreen::LogScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogScreen)
{
    ui->setupUi(this);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &LogScreen::close);
    connect(ui->pushButtonLogIn, &QPushButton::clicked, this, &LogScreen::showMainWindow);

    if(connectToDataBase()) {
        getDataBaseUsers();
    }
}

LogScreen::~LogScreen()
{
    delete ui;
}

void LogScreen::showMainWindow()
{
    if(ui->lineEditPassword->text() == users.userPassword.at(ui->comboBoxUser->currentIndex())) {
        MainWindow *mainWinow = new MainWindow(this, users.userType.at(ui->comboBoxUser->currentIndex()).toInt());
        connect(mainWinow, &MainWindow::windowClosed, this, &LogScreen::show);
        mainWinow->show();
        this->hide();
    } else {
        QMessageBox::information(this, "Błąd logowania", "Nieprawidłowe hasło.", QMessageBox::Ok);
    }
}

bool LogScreen::checkUpdates()
{
    return false;
}

bool LogScreen::connectToDataBase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("10.2.3.46");
    database.setPort(3306);
    database.setDatabaseName("Tester_db");
    database.setUserName("kriskus");
    database.setPassword("7960");
    if(database.open()) {
        ui->labelDataBaseStatus->setText("Połączono z BD");
        return true;
    } else {
        ui->labelDataBaseStatus->setText("Nie połączono z BD");
        return false;
    }
}

void LogScreen::getDataBaseUsers()
{
    QSqlQuery query;
    query.exec("SELECT * FROM Uzytkownicy");
    while(query.next()) {
        users.userName.append(query.value(1).toString());
        users.userPassword.append(query.value(3).toString());
        users.userType.append(query.value(2).toString());
    }

    ui->comboBoxUser->addItems(users.userName);
}

