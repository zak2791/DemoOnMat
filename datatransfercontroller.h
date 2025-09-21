#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "qudpsocket.h"
#include <QObject>

class DataTransferController : public QObject
{
    Q_OBJECT
public:
    explicit DataTransferController(QString*, QObject *parent = nullptr);

    void changeConnection(void);

    ///////////////////////////////////////////////
    /// \brief sendData
    /// \return
    /// отправка данных на компьютер секретаря
    ///
    /// _data - данные
    ///////////////////////////////////////////////
    bool sendData(QString);

private:
    QUdpSocket* udpSocket;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QTcpSocket* clientSocket;
    QString* dataBaseName;
    QString controlCheckSum(QByteArray);
    QObject* p;
    QHostAddress address;
    int portConn;
    int portIn;
    int portOut;
    QByteArray addCheckSum(QString);

private slots:
    void readPendingDatagrams(void);
    void newConnection(void);
    void readyRead(void);

signals:
    void sigConnect(void);
};

#endif // DATATRANSFERCONTROLLER_H
