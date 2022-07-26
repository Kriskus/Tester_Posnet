#ifndef LOGSCREEN_H
#define LOGSCREEN_H

#include <QKeyEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LogScreen; }
QT_END_NAMESPACE

struct User
{
    QStringList userName;
    QStringList userPassword;
    QStringList userType;
};

class LogScreen : public QWidget
{
    Q_OBJECT

public:
    LogScreen(QWidget *parent = nullptr);
    ~LogScreen();

private:
    Ui::LogScreen *ui;
    User users;

    bool closing_{false};

private slots:
    void showMainWindow();
    bool checkUpdates();
    bool connectToDataBase();
    void getDataBaseUsers();
    void closeWindow();
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
};
#endif // LOGSCREEN_H
