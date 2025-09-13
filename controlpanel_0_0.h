#ifndef CONTROLPANEL_____H
#define CONTROLPANEL_____H

#include "controlpanel.h"
#include "qjsonobject.h"
#include "qlineedit.h"
#include "qpushbutton.h"

namespace Ui {
class ControlPanel_0_0;
}

class ControlPanel_0_0 : public ControlPanel
{
    Q_OBJECT

public:
    explicit ControlPanel_0_0(QWidget *parent = nullptr);
    ~ControlPanel_0_0();
    virtual void setData(int, QJsonObject);

private:
    Ui::ControlPanel_0_0 *ui;

    QJsonObject obj;

    int currentTask;
    double totalRate;
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

#endif // CONTROLPANEL_____H
