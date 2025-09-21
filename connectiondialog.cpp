#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup("connections");
    portConn = settings->value("portConn", 5002).toInt();
    portIn = settings->value("portIn", 5001).toInt();
    portOut = settings->value("portOut", 5000).toInt();
    settings->endGroup();

    ui->sbConn->setValue(portConn);
    ui->sbIn->setValue(portIn);
    ui->sbOut->setValue(portOut);

    connect(ui->sbConn, &QSpinBox::valueChanged, this, [this](int value){portConn = value;});
    connect(ui->sbIn, &QSpinBox::valueChanged, this, [this](int value){portIn = value;});
    connect(ui->sbOut, &QSpinBox::valueChanged, this, [this](int value){portOut = value;});


    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConnectionDialog::slotAccepted);

}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::slotAccepted()
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup("connections");
    settings->setValue("portConn", portConn);
    settings->setValue("portIn", portIn);
    settings->setValue("portOut", portOut);
    settings->endGroup();
}
