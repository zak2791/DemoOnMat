#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include "qtcpserver.h"
#include "qudpsocket.h"
#include <QObject>

class DataTransferController : public QObject
{
    Q_OBJECT
public:
    explicit DataTransferController(QObject *parent = nullptr);

    void changeConnection(void);

    ///////////////////////////////////////////////
    /// \brief sendData
    /// \return
    /// отправка данных на компьютер секретаря
    /// _id - id базовой категории
    /// _data - данные
    ///////////////////////////////////////////////
    bool sendData(int _id, QString _data);

private:
    QUdpSocket* udpSocket;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;

private slots:
    void readPendingDatagrams(void);
    void newConnection(void);
    void readyRead(void);

signals:
};

#endif // DATATRANSFERCONTROLLER_H
