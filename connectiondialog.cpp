#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup("connections");
    udpPort = settings->value("udpPort", 5000).toInt();
    tcpPort = settings->value("tcpPort", 5001).toInt();
    settings->endGroup();

    ui->sbPortUDP->setValue(udpPort);
    ui->sbPortTCP->setValue(tcpPort);

    connect(ui->sbPortUDP, &QSpinBox::valueChanged, this, [this](int value){udpPort = value;});
    connect(ui->sbPortTCP, &QSpinBox::valueChanged, this, [this](int value){tcpPort = value;});

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
    settings->setValue("udpPort", udpPort);
    settings->setValue("tcpPort", tcpPort);
    settings->endGroup();
}
