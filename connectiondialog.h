#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include "qsettings.h"
#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

private:
    Ui::ConnectionDialog *ui;

    QSettings* settings;
    int udpPort;
    int tcpPort;
    int httpPort;

private slots:
    void slotAccepted(void);

};

#endif // CONNECTIONDIALOG_H
