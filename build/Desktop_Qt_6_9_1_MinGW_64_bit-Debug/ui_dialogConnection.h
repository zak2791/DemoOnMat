/********************************************************************************
** Form generated from reading UI file 'dialogConnection.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONNECTION_H
#define UI_DIALOGCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_dlgConnection
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *sbPortTCP;
    QSpinBox *sbPortHTTP;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *dlgConnection)
    {
        if (dlgConnection->objectName().isEmpty())
            dlgConnection->setObjectName("dlgConnection");
        dlgConnection->resize(400, 300);
        buttonBox = new QDialogButtonBox(dlgConnection);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        sbPortTCP = new QSpinBox(dlgConnection);
        sbPortTCP->setObjectName("sbPortTCP");
        sbPortTCP->setGeometry(QRect(180, 150, 201, 26));
        sbPortTCP->setMinimum(1000);
        sbPortTCP->setMaximum(50000);
        sbPortTCP->setValue(5000);
        sbPortHTTP = new QSpinBox(dlgConnection);
        sbPortHTTP->setObjectName("sbPortHTTP");
        sbPortHTTP->setGeometry(QRect(180, 190, 201, 26));
        sbPortHTTP->setMinimum(1000);
        sbPortHTTP->setMaximum(50000);
        sbPortHTTP->setValue(5001);
        label = new QLabel(dlgConnection);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 150, 161, 26));
        label_2 = new QLabel(dlgConnection);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(12, 190, 161, 26));

        retranslateUi(dlgConnection);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, dlgConnection, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, dlgConnection, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(dlgConnection);
    } // setupUi

    void retranslateUi(QDialog *dlgConnection)
    {
        dlgConnection->setWindowTitle(QCoreApplication::translate("dlgConnection", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("dlgConnection", "\320\237\320\276\321\200\321\202 TCP \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("dlgConnection", "\320\237\320\276\321\200\321\202 HTTP \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgConnection: public Ui_dlgConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONNECTION_H
