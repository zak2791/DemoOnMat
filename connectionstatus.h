#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include "ledwidget.h"
#include <QWidget>
#include "qtimer.h"

class ConnectionStatus : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionStatus(QWidget *parent = nullptr);

    void setStatusOn(void);

private:
    LEDWidget* ledStatus;
    QTimer* timer;

signals:
};

#endif // CONNECTIONSTATUS_H
