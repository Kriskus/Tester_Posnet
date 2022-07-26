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

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &LogScreen::closeWindow);
    connect(ui->pushButtonLogIn, &QPushButton::clicked, this, &LogScreen::showMainWindow);

    if(connectToDataBase()) {
        getDataBaseUsers();
    }

    ui->labelVersion->setText("ver. 0.0003");
}

LogScreen::~LogScreen() {
    delete ui;
}


void LogScreen::showMainWindow() {
    if(ui->lineEditPassword->text() == users.userPassword.at(ui->comboBoxUser->currentIndex())) {
        MainWindow *mainWindow = new MainWindow(this, users.userType.at(ui->comboBoxUser->currentIndex()).toInt());
        connect(mainWindow, &MainWindow::windowClosed, this, &LogScreen::show);
        connect(mainWindow, &MainWindow::windowClosed, mainWindow, &MainWindow::deleteLater);
        mainWindow->show();
        this->hide();
    } else {
        QMessageBox::information(this, "Błąd logowania", "Nieprawidłowe hasło.", QMessageBox::Ok);
    }
}

bool LogScreen::checkUpdates() {
    return false;
}

bool LogScreen::connectToDataBase() {
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

void LogScreen::getDataBaseUsers() {
    QSqlQuery query;
    query.exec("SELECT * FROM Uzytkownicy");
    while(query.next()) {
        users.userName.append(query.value(1).toString());
        users.userPassword.append(query.value(3).toString());
        users.userType.append(query.value(2).toString());
    }
    ui->comboBoxUser->addItems(users.userName);
}

void LogScreen::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        showMainWindow();
    }
}

void LogScreen::closeWindow() {
    this->close();
}

void LogScreen::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Informacja", "Czy na pewno chcesz zamknąć aplikację?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
