#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "sql/sequencelist.h"
#include "sql/sequencetablesql.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int userType = 0);
    ~MainWindow();

private slots:
    // Main section
    void closeEvent(QCloseEvent *event);
    void showMessageBoxInformation(const QString information);
    void showMessageBoxWarning(const QString warning);
    QMessageBox::StandardButton showMessageBoxQuestion(const QString question);
    void getAllSequence();

    // Sequence section
    void updateSequenceLists(const SequenceList sequences);
    void searchInSequence(const QString text);
    void clearTableWidgetSequence();
    void removeSequenceFromDatabase();

    // Scenario section


    // Test case section


    // Action section


    // Report section


    // Configuration


private:
    Ui::MainWindow *ui;
    SequenceTableSql *sqlSequence_;
    SequenceList seqList_;

    std::pair<int, QString> currentSequence{-1, ""};

    // Main section
    void prepareWindow(int userType);

    // Sequence section
    void prepareSequenceWindowEditor(bool newRecord);
    void showSequenceEditorWindow(bool newRecord);

    // Scenario section


    // Test case section


    // Action section


    // Report section


    // Configuration

signals:
    void refreshSequenceList();
    void sendMessageBoxInformation(QString);
    void sendMessageBoxWarning(QString);
    void windowClosed();
};

#endif // MAINWINDOW_H
