#ifndef SERVER_H
#define SERVER_H

#include "qobject.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

class Server : public QObject
{
public:
    Server(QObject* parent = nullptr);
    void changeConnection(void);

private:
    int port;
    int udpPort;

    QUdpSocket* udpSocket;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;

private slots:
    void slotNewConnection(void);
    void slotServerRead(void);
    void slotClientDisconnected(void);
    void errorOccurred(QAbstractSocket::SocketError);
    void slotDatagram(void);

};



#endif // SERVER_H
