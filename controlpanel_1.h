#ifndef CONTROLPANEL_1_H
#define CONTROLPANEL_1_H

#include "qlineedit.h"
#include "qpushbutton.h"
#include <ControlPanel.h>
#include <QWidget>

namespace Ui {
class ControlPanel_1;
}

class ControlPanel_1 : public ControlPanel
{
    Q_OBJECT

public:
    explicit ControlPanel_1(QWidget *parent = nullptr);
    ~ControlPanel_1();
    virtual void setData(int, QJsonObject);

private:
    Ui::ControlPanel_1 *ui;

    QJsonObject objRed;
    QJsonObject objBlue;

    QJsonObject objFirst;
    QJsonObject objSecond;

    int currentTask;
    double totalRateRed;
    double totalRateBlue;
    double currentTaskRate;
    // double currentTaskRef1Rate;
    // double currentTaskRef2Rate;
    // double currentTaskRef3Rate;
    // double currentTaskRef4Rate;
    // double currentTaskRef5Rate;
    QList<double> lCurrentTaskRate;
    QList<QLineEdit*> leRates;
    QList<QPushButton*> btnErrors;

    void calculateRate1(void);
    void fixResult(void);

    double rate1;               //вычисляемая по ошибкам оценка первого судьи
    QStringList currentErr1;    //ошибки текущего вопроса первого судьи
    QStringList currentErr2;    //
    QStringList currentErr3;    //
    QStringList currentErr4;    //
    QStringList currentErr5;    //

private slots:
    void slotButtonsError(bool);
    void slotEditRate(void);
};

#endif // CONTROLPANEL_1_H
