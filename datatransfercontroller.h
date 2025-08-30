#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include <QObject>

class DataTransferController : public QObject
{
    Q_OBJECT
public:
    explicit DataTransferController(QObject *parent = nullptr);

    void changeConnection(void);

signals:
};

#endif // DATATRANSFERCONTROLLER_H
