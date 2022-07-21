#include "connectionconfiguration.h"
#include "ui_connectionconfiguration.h"

ConnectionConfiguration::ConnectionConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionConfiguration)
{
    ui->setupUi(this);
}

ConnectionConfiguration::~ConnectionConfiguration()
{
    delete ui;
}
