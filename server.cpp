#include "server.h"
#include "qsettings.h"

Server::Server(QObject* parent) : QObject(parent) {

    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("connections");
    port = settings.value("tcpPort", 5000).toInt();
    settings.endGroup();

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

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
        qDebug()<<"read";
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

