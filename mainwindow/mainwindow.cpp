#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql/windows/tableswindoweditor.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

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
    connect(ui->lineEditSearchSequence, &QLineEdit::textChanged, this, &MainWindow::searchInSequence);

    connect(sqlSequence_, &SequenceTableSql::sendError, this, &MainWindow::showMessageBoxWarning);

    ui->tableWidgetSequence->horizontalHeader()->stretchLastSection();
    ui->tableWidgetSequence->setColumnHidden(0, 1);
    ui->tableWidgetSequence->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidgetSequence->horizontalHeader()->hide();

    connect(ui->tableWidgetSequence, &QTableWidget::cellClicked, [this] (int row) {
        currentSequence.first = ui->tableWidgetSequence->item(row, 0)->text().toInt();
        currentSequence.second = ui->tableWidgetSequence->item(row, 1)->text();
    });

    getAllSequence();
    searchInSequence(" ");
}

MainWindow::~MainWindow() {
    delete ui;
    delete sqlSequence_;
}

// Main section

void MainWindow::closeEvent(QCloseEvent* event ) {
    emit windowClosed();
    event->accept();
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

void MainWindow::getAllSequence() {
    sqlSequence_->getAllRecord();
}

void MainWindow::prepareWindow(int userType) {
    ui->tabWidget->tabBar()->setExpanding(true);
    ui->tabWidget->tabBar()->setDocumentMode(true);

    //    connect(ui->comboBoxSequence, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this] (int a) {
    //        if(a >= 0) {
    //            ui->tabWidget->setTabEnabled(0, true);
    //            ui->tabWidget->setTabEnabled(3, true);
    //        }
    //    });

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
        connect(ui->pushButtonAddSequence, &QPushButton::clicked, [this] () { prepareSequenceWindowEditor(true); });
        connect(ui->pushButtonEditSequence, &QPushButton::clicked, [this] () { prepareSequenceWindowEditor(false); });
        connect(ui->pushButtonDeleteSequence, &QPushButton::clicked, this, &MainWindow::removeSequenceFromDatabase);
        break;
    default:
        break;
    }
}

// Sequence section

void MainWindow::updateSequenceLists(const SequenceList sequences) {
    seqList_ = sequences;
    searchInSequence(ui->lineEditSearchSequence->text());
}

void MainWindow::searchInSequence(const QString text) {
    clearTableWidgetSequence();

    for(int i = 0; i < seqList_.name.size(); i++) {
        if(seqList_.name[i].contains(text)){
            ui->tableWidgetSequence->insertRow(ui->tableWidgetSequence->rowCount());
            ui->tableWidgetSequence->setItem(ui->tableWidgetSequence->rowCount()-1, 0, new QTableWidgetItem(seqList_.id[i]));
            ui->tableWidgetSequence->setItem(ui->tableWidgetSequence->rowCount()-1, 1, new QTableWidgetItem(seqList_.name[i]));
        }
    }
    currentSequence.first = -1;
    currentSequence.second = "";
}

void MainWindow::clearTableWidgetSequence() {
    ui->tableWidgetSequence->setRowCount(0);
}

void MainWindow::removeSequenceFromDatabase() {
    if(currentSequence.first == -1) {
        emit sendMessageBoxWarning("Nie wybrano sekwencji do usunięcia!");
    } else {
        if(showMessageBoxQuestion("Czy na pewno chcesz usunąć sekwencję:\n\n" + currentSequence.second + "\n\nz bazy danych?") == QMessageBox::Yes) {
            sqlSequence_->removeRecord(currentSequence.first);
            emit refreshSequenceList();
            emit sendMessageBoxInformation("Sekwencja usunięta");
        }
    }
}

void MainWindow::prepareSequenceWindowEditor(bool newRecord) {
    if(newRecord) {
        showSequenceEditorWindow(true);
    } else {
        if(currentSequence.second == "") {
            QMessageBox::warning(this, "Błąd", "Nie została wybrana sekwencja, którą chcesz edytować!", QMessageBox::Ok);
        } else {
            //showSequenceEditorWindow(false, seqList_.id[ui->comboBoxSequence->currentIndex()].toInt(), seqList_.sequences[ui->comboBoxSequence->currentIndex()]);
            showSequenceEditorWindow(false);
        }
    }
}

void MainWindow::showSequenceEditorWindow(bool newRecord) {
    TablesWindowEditor *tableWindow;
    tableWindow = new TablesWindowEditor(nullptr, 1, newRecord, currentSequence.first, currentSequence.second);
    connect(tableWindow, &TablesWindowEditor::sendError, this, &MainWindow::showMessageBoxWarning);
    connect(tableWindow, &TablesWindowEditor::windowClosed, this, &MainWindow::getAllSequence);
    connect(tableWindow, &TablesWindowEditor::windowClosed, tableWindow, &TablesWindowEditor::deleteLater);
    tableWindow->show();
}




