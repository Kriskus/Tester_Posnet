#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql/windows/sequencewindowsql.h"

#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, int userType) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , sqlSequence_(new SequenceTableSql) {
    ui->setupUi(this);


    prepareWindow(userType);

    connect(sqlSequence_, &SequenceTableSql::sendSequences, this, &MainWindow::updateSequenceLists);
    connect(this, &MainWindow::refreshSequenceList, sqlSequence_, &SequenceTableSql::getAllRecord);
    connect(ui->pushButtonLogout, &QPushButton::clicked, this, &MainWindow::windowClosed);

    connect(this, &MainWindow::sendMessageBoxInformation, this, &MainWindow::showMessageBoxInformation);
    connect(this, &MainWindow::sendMessageBoxWarning, this, &MainWindow::showMessageBoxWarning);

    sqlSequence_->getAllRecord();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::prepareWindow(int userType) {
    ui->tabWidget->tabBar()->setExpanding(true);
    ui->tabWidget->tabBar()->setDocumentMode(true);

    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    ui->tabWidget->setTabEnabled(3, false);
    ui->tabWidget->setTabEnabled(0, false);

    connect(ui->comboBoxSequence, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this] (int a) {
        if(a >= 0) {
            ui->tabWidget->setTabEnabled(0, true);
            ui->tabWidget->setTabEnabled(3, true);
        }
    });

    switch (userType) {
    case 1:
        ui->pushButtonAddSequence->setVisible(0);
        ui->pushButtonEditSequence->setVisible(0);
        ui->pushButtonDeleteSequence->setVisible(0);
        break;
    case 2:
        ui->pushButtonAddSequence->setVisible(1);
        ui->pushButtonEditSequence->setVisible(1);
        ui->pushButtonDeleteSequence->setVisible(1);

        connect(ui->pushButtonAddSequence, &QPushButton::clicked, [this] () {prepareSequenceWindowEditor(true);});
        connect(ui->pushButtonEditSequence, &QPushButton::clicked, [this] () {prepareSequenceWindowEditor(false);});
        //connect(ui->pushButtonDeleteSequence, &QPushButton::clicked, this, &MainWindow::removeSequenceFromDatabase);
        break;
    default:
        break;
    }
}

void MainWindow::prepareSequenceWindowEditor(bool newRecord) {
    if(newRecord) {
        showSequenceEditorWindow(0, "");
    } else {
        if(ui->comboBoxSequence->currentIndex() == -1) {
            QMessageBox::warning(this, "Błąd", "Nie została wybrana sekwencja, którą chcesz edytować!", QMessageBox::Ok);
        } else {
            showSequenceEditorWindow(seqList_.id[ui->comboBoxSequence->currentIndex()].toInt(), seqList_.sequences[ui->comboBoxSequence->currentIndex()]);
        }
    }
}

void MainWindow::showSequenceEditorWindow(int index, const QString sequence) {
    SequenceWindowSQL *sequenceWindow;
    sequenceWindow = new SequenceWindowSQL(this, false, index, sequence);
    connect(sequenceWindow, &SequenceWindowSQL::confirmed, this, &MainWindow::refreshSequenceList);
    connect(sequenceWindow, &SequenceWindowSQL::windowClosed, sequenceWindow, &SequenceWindowSQL::deleteLater);
    sequenceWindow->show();
}

void MainWindow::removeSequenceFromDatabase() {
    if(ui->comboBoxSequence->currentIndex() == -1) {
        emit sendMessageBoxWarning("Nie wybrano sekwencji do usunięcia!");
    } else {
        if(showMessageBoxQuestion("Czy na pewno chcesz usunąć sekwencję:\n" + ui->comboBoxSequence->currentText() + "\nz bazy danych?") == QMessageBox::Yes) {
            sqlSequence_->removeRecord(seqList_.id[ui->comboBoxSequence->currentIndex()].toInt());
            ui->comboBoxSequence->setCurrentIndex(ui->comboBoxSequence->currentIndex() - 1);
            emit refreshSequenceList();
            emit sendMessageBoxInformation("Sekwencja usunięta");
        }
    }
}

void MainWindow::closeEvent(QCloseEvent* event ) {
    emit windowClosed();
    event->accept();
}

void MainWindow::updateSequenceLists(const SequenceList sequences) {
    seqList_ = sequences;
    int temp = ui->comboBoxSequence->currentIndex();
    ui->comboBoxSequence->clear();
    ui->comboBoxSequence->addItems(seqList_.sequences);
    ui->comboBoxSequence->setCurrentIndex(temp);
}

void MainWindow::showMessageBoxInformation(const QString information) {
    QMessageBox::information(this, "Informacja", information, QMessageBox::Ok);
}

void MainWindow::showMessageBoxWarning(const QString warning) {
    QMessageBox::warning(this, "Informacja", warning, QMessageBox::Ok);
}

QMessageBox::StandardButton MainWindow::showMessageBoxQuestion(const QString question) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Ostrzeżenie", question, QMessageBox::Yes|QMessageBox::No);
    return reply;
}
