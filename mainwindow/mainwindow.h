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
    void closeEvent(QCloseEvent *event);
    void updateSequenceLists(const SequenceList sequences);
    void showMessageBoxInformation(const QString information);
    void showMessageBoxWarning(const QString warning);
    QMessageBox::StandardButton showMessageBoxQuestion(const QString question);

private:
    Ui::MainWindow *ui;
    SequenceTableSql *sqlSequence_;
    SequenceList seqList_;

    void prepareWindow(int userType);

    void prepareSequenceWindowEditor(bool newRecord);
    void showSequenceEditorWindow(int index, const QString sequence);
    void removeSequenceFromDatabase();

signals:
    void refreshSequenceList();
    void sendMessageBoxInformation(QString);
    void sendMessageBoxWarning(QString);
    void windowClosed();
};

#endif // MAINWINDOW_H
