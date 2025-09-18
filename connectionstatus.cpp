#include "connectionstatus.h"
#include "qboxlayout.h"
#include "qlabel.h"

ConnectionStatus::ConnectionStatus(QWidget *parent)
    : QWidget{parent}
{
    ledStatus = new LEDWidget(0);
    QLabel* lblMat = new QLabel("Подключено к компьютеру секретаря:");

    QHBoxLayout* hBox = new QHBoxLayout(this);
    hBox->addWidget(lblMat);
    hBox->addWidget(ledStatus);
    hBox->setAlignment(ledStatus, Qt::AlignVCenter);
    setLayout(hBox);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        ledStatus->turnOnOff(false);
    });
}

void ConnectionStatus::setStatusOn()
{
    ledStatus->turnOnOff(true);
    timer->start(6000);
}
