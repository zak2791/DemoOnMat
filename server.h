#ifndef SERVER_H
#define SERVER_H

#include "qobject.h"

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
public:
    Server(QObject* parent = nullptr);
    void setPort(int _port){port = _port;}

private:
    int port;

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;

private slots:
    void slotNewConnection(void);
    void slotServerRead(void);
    void slotClientDisconnected(void);
    void errorOccurred(QAbstractSocket::SocketError);

};



#endif // SERVER_H
