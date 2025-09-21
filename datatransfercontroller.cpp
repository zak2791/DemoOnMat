#include "datatransfercontroller.h"
#include "controller.h"
#include "qdebug.h"
#include "qnetworkdatagram.h"
#include "qsettings.h"

DataTransferController::DataTransferController(QString * _dataBaseName, QObject *parent)
    : QObject{parent}
{

    p = parent;
    dataBaseName = _dataBaseName;

    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    portIn = settings.value("portIn", 5001).toInt();
    portOut = settings.value("portOut", 5000).toInt();
    portConn = settings.value("portConn", 5002).toInt();

    settings.endGroup();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, portConn);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &DataTransferController::readPendingDatagrams);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::acceptError, this, [](QAbstractSocket::SocketError err){
        qDebug()<<err;
    });
    connect(tcpServer, &QTcpServer::newConnection, this, &DataTransferController::newConnection);
    //connect(tcpServer, &QTcpServer::disconnect, this, &DataTransferController::newConnection);

    qDebug()<<tcpServer->listen(QHostAddress::Any, portIn);

    address = QHostAddress();

    clientSocket = new QTcpSocket(this);

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
    //qDebug()<<data;
    if(data.contains("Remove")){
        int id = data.last(data.length() - 6).toInt();
        if(static_cast<Controller*>(p)->removeCategory(id))
            tcpSocket->write("Ok");
        else
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

bool DataTransferController::sendData(QString _data)
{
    qDebug()<<_data<<address;
    if(address.isNull()) return false;
    clientSocket->connectToHost(address, portOut);
    qDebug()<<"conn";
    if(!clientSocket->waitForConnected(1000)){
        clientSocket->close();
        qDebug()<<"conn"<<clientSocket->error();
        return false;
    }
    clientSocket->write(addCheckSum(_data));
    qDebug()<<clientSocket->waitForBytesWritten();
    qDebug()<<"write";
    if(!clientSocket->waitForReadyRead(1000)){
        clientSocket->close();
        qDebug()<<"conn"<<clientSocket->error();
        return false;
    }
    QByteArray ba = clientSocket->readAll();
    clientSocket->close();
    if(ba == "Ok") return true;
    return false;
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
        if(datagram.data() == name){
            udpSocket->writeDatagram("Mat1", datagram.senderAddress(), datagram.senderPort());
            address = datagram.senderAddress();
            emit sigConnect();
        }
        else{
            address = QHostAddress();
        }
    }
}

QByteArray DataTransferController::addCheckSum(QString data)
{
    QByteArray ba = data.toUtf8();
    qint16 checksum = qChecksum(ba);
    //qDebug()<<"c"<<checksum<<ba;
    char a = (checksum & 0xf000)>>12;
    char b = (checksum & 0x0f00)>>8;
    char c = (checksum & 0x00f0)>>4;
    char d = checksum & 0x000f;
    ba.append(a).append(b).append(c).append(d);
    return ba;
}
