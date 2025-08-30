/********************************************************************************
** Form generated from reading UI file 'connectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONDIALOG_H
#define UI_CONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ConnectionDialog
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *sbPortTCP;
    QSpinBox *sbPortHTTP;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *sbPortUDP;
    QLabel *label_3;

    void setupUi(QDialog *ConnectionDialog)
    {
        if (ConnectionDialog->objectName().isEmpty())
            ConnectionDialog->setObjectName("ConnectionDialog");
        ConnectionDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ConnectionDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        sbPortTCP = new QSpinBox(ConnectionDialog);
        sbPortTCP->setObjectName("sbPortTCP");
        sbPortTCP->setGeometry(QRect(180, 140, 201, 26));
        sbPortTCP->setMinimum(1000);
        sbPortTCP->setMaximum(50000);
        sbPortTCP->setValue(5001);
        sbPortHTTP = new QSpinBox(ConnectionDialog);
        sbPortHTTP->setObjectName("sbPortHTTP");
        sbPortHTTP->setGeometry(QRect(180, 180, 201, 26));
        sbPortHTTP->setMinimum(1000);
        sbPortHTTP->setMaximum(50000);
        sbPortHTTP->setValue(5001);
        label_2 = new QLabel(ConnectionDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(12, 180, 161, 26));
        label = new QLabel(ConnectionDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 140, 161, 26));
        sbPortUDP = new QSpinBox(ConnectionDialog);
        sbPortUDP->setObjectName("sbPortUDP");
        sbPortUDP->setGeometry(QRect(180, 100, 201, 26));
        sbPortUDP->setMinimum(1000);
        sbPortUDP->setMaximum(50000);
        sbPortUDP->setValue(5000);
        label_3 = new QLabel(ConnectionDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 161, 26));

        retranslateUi(ConnectionDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ConnectionDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ConnectionDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionDialog)
    {
        ConnectionDialog->setWindowTitle(QCoreApplication::translate("ConnectionDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectionDialog", "\320\237\320\276\321\200\321\202 HTTP \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        label->setText(QCoreApplication::translate("ConnectionDialog", "\320\237\320\276\321\200\321\202 TCP \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectionDialog", "\320\237\320\276\321\200\321\202 UDP \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionDialog: public Ui_ConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONDIALOG_H
