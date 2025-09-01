#include "datatransfercontroller.h"
#include "qdebug.h"

DataTransferController::DataTransferController(QObject *parent)
    : QObject{parent}
{

}

void DataTransferController::changeConnection()
{
    qDebug()<<"changeConnection";
}

bool DataTransferController::sendData(int _id, QString _data)
{
    return true;
}
