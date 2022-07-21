#ifndef CONNECTIONCONFIGURATION_H
#define CONNECTIONCONFIGURATION_H

#include <QWidget>

namespace Ui {
class ConnectionConfiguration;
}

class ConnectionConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionConfiguration(QWidget *parent = nullptr);
    ~ConnectionConfiguration();

private:
    Ui::ConnectionConfiguration *ui;
};

#endif // CONNECTIONCONFIGURATION_H
