#include "datatransfercontroller.h"
#include "qdebug.h"
#include "qnetworkdatagram.h"
#include "qtcpsocket.h"

DataTransferController::DataTransferController(QObject *parent)
    : QObject{parent}
{

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 5000);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &DataTransferController::readPendingDatagrams);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::acceptError, this, [](QAbstractSocket::SocketError err){
        qDebug()<<err;
    });
    connect(tcpServer, &QTcpServer::newConnection, this, &DataTransferController::newConnection);
    //     qDebug()<<"next";
    //     tcpSocket = tcpServer->nextPendingConnection();
    //     if(!tcpSocket->waitForReadyRead(1000)){
    //         qDebug()<<"wait error";
    //         delete tcpSocket;
    //         return;
    //     }
    //     QByteArray ba = tcpSocket->readAll();
    //     //checksum!!! & write to database & check exists record
    //     qDebug()<<ba;
    //     tcpSocket->write("Ok");
    //     tcpSocket->waitForBytesWritten(1000);
    //     tcpSocket->close();
    //     delete tcpSocket;
    // });
    qDebug()<<tcpServer->listen(QHostAddress::Any, 5001);



}

void DataTransferController::newConnection()
{
    qDebug() << "Get connected";
    tcpSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    qDebug() << "Get connected";

    /*socket->write("Hello client!");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
*/

}

void DataTransferController::readyRead()
{
    qDebug() << "Got read-signal," << tcpSocket->bytesAvailable() << "bytes.";
    QByteArray input = tcpSocket->readAll();
    qDebug() << "Input:" << input << "\nReturning...";
    tcpSocket->write(input);
    tcpSocket->close();
    qDebug() << "Returned.\nListening...";
}

void DataTransferController::changeConnection()
{
    qDebug()<<"changeConnection";
}

bool DataTransferController::sendData(int _id, QString _data)
{
    return true;
}

void DataTransferController::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        qDebug()<<datagram.data()<<datagram.senderAddress()<<datagram.senderPort();
        udpSocket->writeDatagram("Mat1", datagram.senderAddress(), datagram.senderPort());
    }
}
