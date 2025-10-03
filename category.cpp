#include "category.h"

Category::Category(
    int _id,
    int _id_base,
    int _status,
    QString _category,
    QString _age,
    QString _weight,
    QString _data,
    QWidget* parent):QFrame(parent)
{

    id = _id;
    id_base = _id_base;
    status = _status;
    category = _category;
    age = _age;
    weight = _weight;
    data = _data;
    btnSending = new QPushButton("Отправить секретарю");
    connect(btnSending, &QPushButton::clicked, this, &Category::slotSendingData);

    setFrameStyle(QFrame::WinPanel);

    QList<QFrame*> lFrame;
    for(int i = 0; i < 4; i++){
        QFrame* line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        lFrame.append(line);
    }

    layout = new QVBoxLayout(this);
    hbFirstRow = new QHBoxLayout(this);

    lblCategory.setText(category);
    //lblCategory.setFrameStyle(QFrame::NoFrame);
    lblAge.setText(age);
    lblWeight.setText(weight);
    ledStatus = new LEDWidget(0);

    hbFirstRow->addWidget(&lblCategory);
    hbFirstRow->addWidget(lFrame.at(0));
    hbFirstRow->addWidget(&lblAge);
    hbFirstRow->addWidget(lFrame.at(1));
    hbFirstRow->addWidget(&lblWeight);
    hbFirstRow->addWidget(lFrame.at(2));
    hbFirstRow->addWidget(&lblStage);
    hbFirstRow->addStretch();
    hbFirstRow->addWidget(lFrame.at(3));
    hbFirstRow->addWidget(new QLabel("Результаты у секретаря"));
    hbFirstRow->addWidget(ledStatus);
    hbFirstRow->addWidget(btnSending);

    QLayout* lay = hbFirstRow->layout();
    lay->setAlignment(ledStatus, Qt::AlignVCenter);

    layout->addLayout(hbFirstRow);
    setLayout(layout);

    if(status == 3) ledStatus->turnOnOff(true);
}

void Category::setDataFromControlPanel(QJsonObject)
{

}

int Category::getStatus(){
    return status;
}

void Category::setStatus(int _status)
{
    if(_status == 0 && status > 1) return;
    status = _status;
    if(status == 2) ledStatus->turnOnOff(false);
    if(status == 3) ledStatus->turnOnOff(true);
}

void Category::slotSendingData()
{
    qDebug()<<"send";
}

void Category::setSendingStatus()
{

}
