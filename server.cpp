#include "server.h"
#include "qsettings.h"

#include <QNetworkDatagram>

Server::Server(QObject* parent) : QObject(parent) {

    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("connections");
    udpPort = settings.value("udpPort", 5000).toInt();
    port = settings.value("tcpPort", 5001).toInt();
    settings.endGroup();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, udpPort);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Server::slotDatagram);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if(!tcpServer->listen(QHostAddress::Any, port)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }

}

void Server::changeConnection()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("connections");
    udpPort = settings.value("udpPort", 5000).toInt();
    port = settings.value("tcpPort", 5000).toInt();
    settings.endGroup();
    tcpServer->close();
    if(!tcpServer->listen(QHostAddress::Any, port)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}


void Server::slotNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();

    tcpSocket->write("Hello, World!!! I am echo server!\r\n");

    connect(tcpSocket, &QTcpSocket::readyRead, this, &Server::slotServerRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &Server::errorOccurred);
    qDebug()<<"new";
}

void Server::slotServerRead()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray array = tcpSocket->readAll();

        tcpSocket->write("it's i'm");
        qDebug()<<"read"<<array;
    }
}

void Server::slotClientDisconnected()
{
    tcpSocket->close();
    qDebug()<<"close";
}

void Server::errorOccurred(QAbstractSocket::SocketError error)
{
    qDebug()<<error;
}

void Server::slotDatagram()
{
    QNetworkDatagram datagram;
    while(udpSocket->hasPendingDatagrams()){
        datagram = udpSocket->receiveDatagram();
    }
    qDebug()<<datagram.data();

    QNetworkDatagram replyDatagram(QByteArray("Ok"), datagram.senderAddress(), datagram.senderPort());

    udpSocket->writeDatagram(replyDatagram);
}

