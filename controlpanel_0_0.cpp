#include "controlpanel_0_0.h"
#include "ui_controlpanel_0_0.h"

ControlPanel_0_0::ControlPanel_0_0(QWidget *parent)
    : ControlPanel(parent)
    , ui(new Ui::ControlPanel_0_0)
{
    ui->setupUi(this);

    leRates.append({ui->le1, ui->le2, ui->le3, ui->le4, ui->le5});
    btnErrors.append({ui->btnErr01, ui->btnErr02,  ui->btnErr03,  ui->btnErr04, ui->btnErr05,
                           ui->btnErr06,  ui->btnErr07,  ui->btnErr08, ui->btnErr09,  ui->btnErr10,
                           ui->btnErr11,  ui->btnErr12, ui->btnErr13,  ui->btnErr14,  ui->btnErr15});

    foreach(auto each, btnErrors)
        connect(each, &QPushButton::clicked, this, &ControlPanel_0_0::slotButtonsError);

    connect(ui->btnZero, &QPushButton::clicked, this, [this](bool check){
        if(check) currentErr1.append("0");
        else currentErr1.removeOne("0");
        calculateRate1();
    });
    connect(ui->btnPlus1, &QPushButton::clicked, this, [this](bool check){
        if(check) currentErr1.append("+1");
        else currentErr1.removeOne("+1");
        calculateRate1();
    });
    connect(ui->btnMinus2, &QPushButton::clicked, this, [this](bool check){
        if(check) currentErr1.append("-2");
        else currentErr1.removeOne("-2");
        calculateRate1();
    });
    foreach(auto each, leRates)
        connect(each, &QLineEdit::editingFinished, this, &ControlPanel_0_0::slotEditRate);

    connect(ui->btnNext, &QPushButton::clicked, this, [this](){
        currentTask++;
        currentErr1.clear();
        ui->lblTaskSum->clear();
        foreach(auto each, leRates){
            each->setStyleSheet("background-color: white");
            each->setEnabled(true);
            each->clear();
        }

        ui->lblTask->setText(QString::number(currentTask));
        ui->btnNext->setEnabled(false);
        ui->btnFix->setEnabled(true);
        QList<QPushButton*> lBtn = findChildren<QPushButton*>();
        foreach(auto each, lBtn){
            QString name = each->objectName();
            if(name == "btnPlus1" || name == "btnZero" || name == "btnMinus2"){
                each->setChecked(false);
                each->setEnabled(true);
            }
            else{
                bool ok;
                name.last(2).toInt(&ok);
                if(ok){
                    each->setChecked(false);
                    each->setEnabled(true);
                }
            }
        }
    });
    connect(ui->btnFix, &QPushButton::clicked, this, [this](){
        foreach(auto each, leRates)
            if(each->text() == "") return;

        foreach(auto each, leRates)
            if(each->text() == "") each->setEnabled(false);

        if(currentTask < 5)
            ui->btnNext->setEnabled(true);

        ui->btnFix->setEnabled(false);

        foreach(auto each, btnErrors)
            each->setEnabled(false);

        ui->btnZero->setEnabled(false);
        ui->btnPlus1->setEnabled(false);
        ui->btnMinus2->setEnabled(false);

        fixResult();
    });
}

ControlPanel_0_0::~ControlPanel_0_0()
{
    delete ui;
}

void ControlPanel_0_0::setData(int id, QJsonObject _obj)
{
    obj = _obj;
    totalRate =obj.value("TotalRate").toDouble();

    currentTaskRate = 0.0;
    ui->lblName->setText(obj.value("Name").toString());
    ui->lblTeam->setText(obj.value("Team").toString());
    lCurrentTaskRate.clear();

    id_category = id;
    currentTask = obj.value("CurrentTask").toInt();

    ui->lblTask->clear();
    ui->lblTotal->clear();
    ui->lblTaskSum->clear();

    if(currentTask == 5) ui->btnNext->setEnabled(false);
    else ui->btnNext->setEnabled(true);

    ui->btnFix->setEnabled(false);

    foreach(auto each, leRates){
        each->setStyleSheet("background-color: white");
        each->clear();
    }

    if(currentTask == 1){
        lCurrentTaskRate.append(obj.value("Task1Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task1Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task1Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task1Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task1Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = obj.value("Task1Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 2){
        lCurrentTaskRate.append(obj.value("Task2Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task2Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task2Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task2Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task2Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = obj.value("Task2Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 3){
        lCurrentTaskRate.append(obj.value("Task3Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task3Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task3Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task3Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task3Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = obj.value("Task3Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 4){
        lCurrentTaskRate.append(obj.value("Task4Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task4Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task4Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task4Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task4Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = obj.value("Task4Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 5){
        lCurrentTaskRate.append(obj.value("Task5Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task5Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task5Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task5Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(obj.value("Task5Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = obj.value("Task5Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask > 0){
        ui->lblTask->setText(QString::number(currentTask));
        ui->lblTotal->setText(QString::number(totalRate));
        int min = 0;
        int max = 4;
        for(int i = 1; i < 5; i++){
            if(lCurrentTaskRate.at(min) > lCurrentTaskRate.at(i)) min = i;
            if(lCurrentTaskRate.at(max) < lCurrentTaskRate.at(4 - i)) max = 4 - i;
        }
        for(int i = 0; i < 5; i++){
            if(i == min) leRates.at(i)->setStyleSheet("background-color: blue");
            else if(i == max) leRates.at(i)->setStyleSheet("background-color: red");
        }
    }
}

void ControlPanel_0_0::calculateRate1()
{
    if(currentErr1.contains("0")){
        rate1 = 0.0;
    }
    else{
        rate1 = 10.0;
        foreach (auto each, currentErr1) {
            if(each == "+1") rate1 += 1.0;
            else if(each == "-2") rate1 -= 2.0;
            else{
                int err = each.toInt();
                if(err < 6) rate1 -= 0.5;
                else if(err < 11) rate1 -= 1.0;
                else rate1 -= 2.0;
            }
        }
        rate1 = rate1 < 0 ? 0 : rate1;
    }
    ui->le1->setText(QString::number(rate1));
}

void ControlPanel_0_0::fixResult()
{
    currentTaskRate = 0;
    lCurrentTaskRate.clear();
    lCurrentTaskRate.append(ui->le1->text().toDouble());
    lCurrentTaskRate.append(ui->le2->text().toDouble());
    lCurrentTaskRate.append(ui->le3->text().toDouble());
    lCurrentTaskRate.append(ui->le4->text().toDouble());
    lCurrentTaskRate.append(ui->le5->text().toDouble());
    int min = 0;
    int max = 4;
    for(int i = 1; i < 5; i++){
        if(lCurrentTaskRate.at(min) > lCurrentTaskRate.at(i)) min = i;
        if(lCurrentTaskRate.at(max) < lCurrentTaskRate.at(4 - i)) max = 4 - i;
    }
    for(int i = 0; i < 5; i++){
        if(i == min) leRates.at(i)->setStyleSheet("background-color: blue");
        else if(i == max) leRates.at(i)->setStyleSheet("background-color: red");
        else currentTaskRate += leRates.at(i)->text().toDouble();

    }

    ui->lblTaskSum->setText(QString::number(currentTaskRate));
    totalRate += currentTaskRate;
    ui->lblTotal->setText(QString::number(totalRate));

    obj.insert("CurrentTask", currentTask);
    if(currentTask == 1){
        obj.insert("Task1Ref1Rate", lCurrentTaskRate.at(0));
        obj.insert("Task1Ref2Rate", lCurrentTaskRate.at(1));
        obj.insert("Task1Ref3Rate", lCurrentTaskRate.at(2));
        obj.insert("Task1Ref4Rate", lCurrentTaskRate.at(3));
        obj.insert("Task1Ref5Rate", lCurrentTaskRate.at(4));

        obj.insert("Task1Ref1Err", currentErr1.join(";"));
        obj.insert("Task1Ref2Err", currentErr2.join(";"));
        obj.insert("Task1Ref3Err", currentErr3.join(";"));
        obj.insert("Task1Ref4Err", currentErr4.join(";"));
        obj.insert("Task1Ref5Err", currentErr5.join(";"));

        obj.insert("Task1Rate", currentTaskRate);
        obj.insert("TotalRate", totalRate);
    }
    else if(currentTask == 2){
        obj.insert("Task2Ref1Rate", lCurrentTaskRate.at(0));
        obj.insert("Task2Ref2Rate", lCurrentTaskRate.at(1));
        obj.insert("Task2Ref3Rate", lCurrentTaskRate.at(2));
        obj.insert("Task2Ref4Rate", lCurrentTaskRate.at(3));
        obj.insert("Task2Ref5Rate", lCurrentTaskRate.at(4));

        obj.insert("Task2Ref1Err", currentErr1.join(";"));
        obj.insert("Task2Ref2Err", currentErr2.join(";"));
        obj.insert("Task2Ref3Err", currentErr3.join(";"));
        obj.insert("Task2Ref4Err", currentErr4.join(";"));
        obj.insert("Task2Ref5Err", currentErr5.join(";"));

        obj.insert("Task2Rate", currentTaskRate);
        obj.insert("TotalRate", totalRate);
    }
    else if(currentTask == 3){
        obj.insert("Task3Ref1Rate", lCurrentTaskRate.at(0));
        obj.insert("Task3Ref2Rate", lCurrentTaskRate.at(1));
        obj.insert("Task3Ref3Rate", lCurrentTaskRate.at(2));
        obj.insert("Task3Ref4Rate", lCurrentTaskRate.at(3));
        obj.insert("Task3Ref5Rate", lCurrentTaskRate.at(4));

        obj.insert("Task3Ref1Err", currentErr1.join(";"));
        obj.insert("Task3Ref2Err", currentErr2.join(";"));
        obj.insert("Task3Ref3Err", currentErr3.join(";"));
        obj.insert("Task3Ref4Err", currentErr4.join(";"));
        obj.insert("Task3Ref5Err", currentErr5.join(";"));

        obj.insert("Task3Rate", currentTaskRate);
        obj.insert("TotalRate", totalRate);
    }
    else if(currentTask == 4){
        obj.insert("Task4Ref1Rate", lCurrentTaskRate.at(0));
        obj.insert("Task4Ref2Rate", lCurrentTaskRate.at(1));
        obj.insert("Task4Ref3Rate", lCurrentTaskRate.at(2));
        obj.insert("Task4Ref4Rate", lCurrentTaskRate.at(3));
        obj.insert("Task4Ref5Rate", lCurrentTaskRate.at(4));

        obj.insert("Task4Ref1Err", currentErr1.join(";"));
        obj.insert("Task4Ref2Err", currentErr2.join(";"));
        obj.insert("Task4Ref3Err", currentErr3.join(";"));
        obj.insert("Task4Ref4Err", currentErr4.join(";"));
        obj.insert("Task4Ref5Err", currentErr5.join(";"));

        obj.insert("Task4Rate", currentTaskRate);
        obj.insert("TotalRate", totalRate);
    }
    else{
        obj.insert("Task5Ref1Rate", lCurrentTaskRate.at(0));
        obj.insert("Task5Ref2Rate", lCurrentTaskRate.at(1));
        obj.insert("Task5Ref3Rate", lCurrentTaskRate.at(2));
        obj.insert("Task5Ref4Rate", lCurrentTaskRate.at(3));
        obj.insert("Task5Ref5Rate", lCurrentTaskRate.at(4));

        obj.insert("Task5Ref1Err", currentErr1.join(";"));
        obj.insert("Task5Ref2Err", currentErr2.join(";"));
        obj.insert("Task5Ref3Err", currentErr3.join(";"));
        obj.insert("Task5Ref4Err", currentErr4.join(";"));
        obj.insert("Task5Ref5Err", currentErr5.join(";"));

        obj.insert("Task5Rate", currentTaskRate);
        obj.insert("TotalRate", totalRate);
    }

    emit sigFixResult(id_category, obj);

}

void ControlPanel_0_0::slotButtonsError(bool check)
{
    int num = sender()->objectName().last(2).toInt();
    if(check) currentErr1.append(QString::number(num));
    else currentErr1.removeOne(QString::number(num));
    calculateRate1();
}

void ControlPanel_0_0::slotEditRate()
{
    QLineEdit* le = static_cast<QLineEdit*>(sender());
    bool ok;
    double d = le->text().toDouble(&ok);
    if(!ok || (d > 11 || d < 0)) le->setText("");
}

