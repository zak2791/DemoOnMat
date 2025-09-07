#include "datatransfercontroller.h"
#include "controller.h"
#include "qdebug.h"
#include "qnetworkdatagram.h"
#include "qtcpsocket.h"

DataTransferController::DataTransferController(QString * _dataBaseName, QObject *parent)
    : QObject{parent}
{

    p = parent;
    dataBaseName = _dataBaseName;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 5000);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &DataTransferController::readPendingDatagrams);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::acceptError, this, [](QAbstractSocket::SocketError err){
        qDebug()<<err;
    });
    connect(tcpServer, &QTcpServer::newConnection, this, &DataTransferController::newConnection);
    //connect(tcpServer, &QTcpServer::disconnect, this, &DataTransferController::newConnection);

    qDebug()<<tcpServer->listen(QHostAddress::Any, 5001);



}

void DataTransferController::newConnection()
{
    qDebug() << "Get connected";
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(tcpSocket, &QTcpSocket::disconnected, this, [this](){
        qDebug()<<"disconnected";
        tcpSocket->deleteLater();
    });
}

void DataTransferController::readyRead()
{
    qDebug() << "Got read-signal," << tcpSocket->bytesAvailable() << "bytes.";
    QByteArray input = tcpSocket->readAll();
    qDebug()<<input;
    QString data = controlCheckSum(input);
    if(data == ""){
        tcpSocket->write("Err");
        return;
    }
    if((static_cast<Controller*>(p))->addCategory(data))
        tcpSocket->write("Ok");
    else
        tcpSocket->write("Err");
    // tcpSocket->close();
    qDebug() << data;
}

void DataTransferController::changeConnection()
{
    qDebug()<<"changeConnection";
}

bool DataTransferController::sendData(int _id, QString _data)
{
    return true;
}

QString DataTransferController::controlCheckSum(QByteArray _ba)
{
    QByteArray ba = _ba;
    char a = ba.at(ba.length() - 4);
    char b = ba.at(ba.length() - 3);
    char c = ba.at(ba.length() - 2);
    char d = ba.at(ba.length() - 1);
    qint16 check = ((qint16)a)<<12 | ((qint16)b)<<8 |((qint16)c)<<4 | (qint16)d;
    ba = ba.first(ba.length() - 4);
    if((qint16)qChecksum(ba) == check) return QString(ba);
    else return "";
}

void DataTransferController::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString name = *dataBaseName;
        int len = name.length();
        if(len < 6) return;
        name = name.first(len - 5);
        qDebug()<<datagram.data();
        if(datagram.data() == name)
            udpSocket->writeDatagram("Mat1", datagram.senderAddress(), datagram.senderPort());
    }
}
