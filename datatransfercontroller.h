#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

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

signals:
};

#endif // DATATRANSFERCONTROLLER_H
