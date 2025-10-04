#include "controlpanel_1.h"
#include "qjsonarray.h"
#include "ui_controlpanel_1.h"

ControlPanel_1::ControlPanel_1(QWidget *parent)
    : ControlPanel(parent)
    , ui(new Ui::ControlPanel_1)
{
    ui->setupUi(this);

    id_system = 1;

    leRates.append({ui->le1, ui->le2, ui->le3, ui->le4, ui->le5});
    btnErrors.append({ui->btnErr01, ui->btnErr02,  ui->btnErr03,  ui->btnErr04, ui->btnErr05,
                      ui->btnErr06,  ui->btnErr07,  ui->btnErr08, ui->btnErr09,  ui->btnErr10,
                      ui->btnErr11,  ui->btnErr12, ui->btnErr13,  ui->btnErr14,  ui->btnErr15});

    foreach(auto each, btnErrors)
        connect(each, &QPushButton::clicked, this, &ControlPanel_1::slotButtonsError);

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
        connect(each, &QLineEdit::editingFinished, this, &ControlPanel_1::slotEditRate);

    connect(ui->btnNext, &QPushButton::clicked, this, [this](){
        currentTask++;
        currentErr1.clear();
        ui->lblTaskSum->clear();
        foreach(auto each, leRates){
            each->setStyleSheet("background-color: white");
            each->setEnabled(true);
            each->clear();
        }

        int iTask = (currentTask + 1 - (currentTask + 1) % 2) / 2;
        ui->lblTask->setText(QString::number(iTask));
        if(ui->rbRed->isChecked()){
            if(currentTask % 2 == 1)
                ui->lblTask->setStyleSheet("QLabel{color: red}");
            else
                ui->lblTask->setStyleSheet("QLabel{color: blue}");
        }
        else{
            if(currentTask % 2 != 1)
                ui->lblTask->setStyleSheet("QLabel{color: red}");
            else
                ui->lblTask->setStyleSheet("QLabel{color: blue}");
        }

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

        if(currentTask < 10)
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

ControlPanel_1::~ControlPanel_1()
{
    delete ui;
}

void ControlPanel_1::setData(int id, QJsonObject _obj)
{
    objRed = _obj.value("Red").toObject();
    objBlue = _obj.value("Blue").toObject();

    totalRateRed =objRed.value("TotalRate").toDouble();
    totalRateBlue =objBlue.value("TotalRate").toDouble();

    currentTaskRate = 0.0;
    ui->lblNameRed->setText(objRed.value("Name").toString());
    ui->lblTeamRed->setText(objRed.value("Team").toString());
    ui->lblNameBlue->setText(objBlue.value("Name").toString());
    ui->lblTeamBlue->setText(objBlue.value("Team").toString());
    lCurrentTaskRate.clear();

    id_category = id;
    currentTask = objRed.value("CurrentTask").toInt();

    ui->lblTask->clear();
    ui->lblTotalRed->clear();
    ui->lblTotalBlue->clear();
    ui->lblTaskSum->clear();

    if(currentTask == 10) ui->btnNext->setEnabled(false);
    else ui->btnNext->setEnabled(true);

    ui->btnFix->setEnabled(false);

    foreach(auto each, leRates){
        each->setStyleSheet("background-color: white");
        each->clear();
    }

    if(ui->rbRed->isChecked()){
        objFirst = objRed;
        objSecond = objBlue;
    }
    else{
        objFirst = objBlue;
        objSecond = objRed;
    }
    if(currentTask == 1){
        lCurrentTaskRate.append(objFirst.value("Task1Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task1Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task1Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task1Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task1Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objFirst.value("Task1Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 2){
        lCurrentTaskRate.append(objSecond.value("Task1Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task1Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task1Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task1Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task1Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objSecond.value("Task1Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 3){
        lCurrentTaskRate.append(objFirst.value("Task2Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task2Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task2Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task2Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task2Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objFirst.value("Task2Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 4){
        lCurrentTaskRate.append(objSecond.value("Task2Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task2Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task2Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task2Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task2Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objSecond.value("Task2Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 5){
        lCurrentTaskRate.append(objFirst.value("Task3Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task3Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task3Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task3Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task3Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objFirst.value("Task3Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 6){
        lCurrentTaskRate.append(objSecond.value("Task3Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task3Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task3Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task3Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task3Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objSecond.value("Task3Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 7){
        lCurrentTaskRate.append(objFirst.value("Task4Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task4Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task4Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task4Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task4Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objFirst.value("Task4Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 8){
        lCurrentTaskRate.append(objSecond.value("Task4Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task4Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task4Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task4Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task4Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objSecond.value("Task4Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 9){
        lCurrentTaskRate.append(objFirst.value("Task5Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task5Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task5Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task5Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objFirst.value("Task5Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objFirst.value("Task5Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask == 10){
        lCurrentTaskRate.append(objSecond.value("Task5Ref1Rate").toDouble());
        leRates.at(0)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task5Ref2Rate").toDouble());
        leRates.at(1)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task5Ref3Rate").toDouble());
        leRates.at(2)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task5Ref4Rate").toDouble());
        leRates.at(3)->setText(QString::number(lCurrentTaskRate.last()));

        lCurrentTaskRate.append(objSecond.value("Task5Ref5Rate").toDouble());
        leRates.at(4)->setText(QString::number(lCurrentTaskRate.last()));

        currentTaskRate = objSecond.value("Task5Rate").toDouble();
        ui->lblTaskSum->setText(QString::number(currentTaskRate));
    }
    if(currentTask > 0){
        int iTask = (currentTask + 1 - (currentTask + 1) % 2) / 2;
        ui->lblTask->setText(QString::number(iTask));
        if(ui->rbRed->isChecked()){
            if(currentTask % 2 == 1)
                ui->lblTask->setStyleSheet("QLabel{color: red}");
            else
                ui->lblTask->setStyleSheet("QLabel{color: blue}");
        }
        else{
            if(currentTask % 2 != 1)
                ui->lblTask->setStyleSheet("QLabel{color: red}");
            else
                ui->lblTask->setStyleSheet("QLabel{color: blue}");
        }
        ui->lblTotalRed->setText(QString::number(totalRateRed));
        ui->lblTotalBlue->setText(QString::number(totalRateBlue));
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

void ControlPanel_1::calculateRate1()
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

void ControlPanel_1::fixResult()
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
    //totalRate += currentTaskRate;
    //ui->lblTotal->setText(QString::number(totalRate));

    objRed.insert("CurrentTask", currentTask);
    if(currentTask == 1){
        objFirst.insert("Task1Ref1Rate", lCurrentTaskRate.at(0));
        objFirst.insert("Task1Ref2Rate", lCurrentTaskRate.at(1));
        objFirst.insert("Task1Ref3Rate", lCurrentTaskRate.at(2));
        objFirst.insert("Task1Ref4Rate", lCurrentTaskRate.at(3));
        objFirst.insert("Task1Ref5Rate", lCurrentTaskRate.at(4));

        objFirst.insert("Task1Ref1Err", currentErr1.join(";"));
        objFirst.insert("Task1Ref2Err", currentErr2.join(";"));
        objFirst.insert("Task1Ref3Err", currentErr3.join(";"));
        objFirst.insert("Task1Ref4Err", currentErr4.join(";"));
        objFirst.insert("Task1Ref5Err", currentErr5.join(";"));

        objFirst.insert("Task1Rate", currentTaskRate);
        //obj.insert("TotalRate", totalRate);
    }
    else if(currentTask == 2){
        objSecond.insert("Task1Ref1Rate", lCurrentTaskRate.at(0));
        objSecond.insert("Task1Ref2Rate", lCurrentTaskRate.at(1));
        objSecond.insert("Task1Ref3Rate", lCurrentTaskRate.at(2));
        objSecond.insert("Task1Ref4Rate", lCurrentTaskRate.at(3));
        objSecond.insert("Task1Ref5Rate", lCurrentTaskRate.at(4));

        objSecond.insert("Task1Ref1Err", currentErr1.join(";"));
        objSecond.insert("Task1Ref2Err", currentErr2.join(";"));
        objSecond.insert("Task1Ref3Err", currentErr3.join(";"));
        objSecond.insert("Task1Ref4Err", currentErr4.join(";"));
        objSecond.insert("Task1Ref5Err", currentErr5.join(";"));

        objSecond.insert("Task2Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 3){
        objFirst.insert("Task2Ref1Rate", lCurrentTaskRate.at(0));
        objFirst.insert("Task2Ref2Rate", lCurrentTaskRate.at(1));
        objFirst.insert("Task2Ref3Rate", lCurrentTaskRate.at(2));
        objFirst.insert("Task2Ref4Rate", lCurrentTaskRate.at(3));
        objFirst.insert("Task2Ref5Rate", lCurrentTaskRate.at(4));

        objFirst.insert("Task2Ref1Err", currentErr1.join(";"));
        objFirst.insert("Task2Ref2Err", currentErr2.join(";"));
        objFirst.insert("Task2Ref3Err", currentErr3.join(";"));
        objFirst.insert("Task2Ref4Err", currentErr4.join(";"));
        objFirst.insert("Task2Ref5Err", currentErr5.join(";"));

        objFirst.insert("Task3Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 4){
        objSecond.insert("Task2Ref1Rate", lCurrentTaskRate.at(0));
        objSecond.insert("Task2Ref2Rate", lCurrentTaskRate.at(1));
        objSecond.insert("Task2Ref3Rate", lCurrentTaskRate.at(2));
        objSecond.insert("Task2Ref4Rate", lCurrentTaskRate.at(3));
        objSecond.insert("Task2Ref5Rate", lCurrentTaskRate.at(4));

        objSecond.insert("Task2Ref1Err", currentErr1.join(";"));
        objSecond.insert("Task2Ref2Err", currentErr2.join(";"));
        objSecond.insert("Task2Ref3Err", currentErr3.join(";"));
        objSecond.insert("Task2Ref4Err", currentErr4.join(";"));
        objSecond.insert("Task2Ref5Err", currentErr5.join(";"));

        objSecond.insert("Task2Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 5){
        objFirst.insert("Task3Ref1Rate", lCurrentTaskRate.at(0));
        objFirst.insert("Task3Ref2Rate", lCurrentTaskRate.at(1));
        objFirst.insert("Task3Ref3Rate", lCurrentTaskRate.at(2));
        objFirst.insert("Task3Ref4Rate", lCurrentTaskRate.at(3));
        objFirst.insert("Task3Ref5Rate", lCurrentTaskRate.at(4));

        objFirst.insert("Task3Ref1Err", currentErr1.join(";"));
        objFirst.insert("Task3Ref2Err", currentErr2.join(";"));
        objFirst.insert("Task3Ref3Err", currentErr3.join(";"));
        objFirst.insert("Task3Ref4Err", currentErr4.join(";"));
        objFirst.insert("Task3Ref5Err", currentErr5.join(";"));

        objFirst.insert("Task3Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 6){
        objSecond.insert("Task3Ref1Rate", lCurrentTaskRate.at(0));
        objSecond.insert("Task3Ref2Rate", lCurrentTaskRate.at(1));
        objSecond.insert("Task3Ref3Rate", lCurrentTaskRate.at(2));
        objSecond.insert("Task3Ref4Rate", lCurrentTaskRate.at(3));
        objSecond.insert("Task3Ref5Rate", lCurrentTaskRate.at(4));

        objSecond.insert("Task3Ref1Err", currentErr1.join(";"));
        objSecond.insert("Task3Ref2Err", currentErr2.join(";"));
        objSecond.insert("Task3Ref3Err", currentErr3.join(";"));
        objSecond.insert("Task3Ref4Err", currentErr4.join(";"));
        objSecond.insert("Task3Ref5Err", currentErr5.join(";"));

        objSecond.insert("Task3Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 7){
        objFirst.insert("Task4Ref1Rate", lCurrentTaskRate.at(0));
        objFirst.insert("Task4Ref2Rate", lCurrentTaskRate.at(1));
        objFirst.insert("Task4Ref3Rate", lCurrentTaskRate.at(2));
        objFirst.insert("Task4Ref4Rate", lCurrentTaskRate.at(3));
        objFirst.insert("Task4Ref5Rate", lCurrentTaskRate.at(4));

        objFirst.insert("Task4Ref1Err", currentErr1.join(";"));
        objFirst.insert("Task4Ref2Err", currentErr2.join(";"));
        objFirst.insert("Task4Ref3Err", currentErr3.join(";"));
        objFirst.insert("Task4Ref4Err", currentErr4.join(";"));
        objFirst.insert("Task4Ref5Err", currentErr5.join(";"));

        objFirst.insert("Task3Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 8){
        objSecond.insert("Task4Ref1Rate", lCurrentTaskRate.at(0));
        objSecond.insert("Task4Ref2Rate", lCurrentTaskRate.at(1));
        objSecond.insert("Task4Ref3Rate", lCurrentTaskRate.at(2));
        objSecond.insert("Task4Ref4Rate", lCurrentTaskRate.at(3));
        objSecond.insert("Task4Ref5Rate", lCurrentTaskRate.at(4));

        objSecond.insert("Task4Ref1Err", currentErr1.join(";"));
        objSecond.insert("Task4Ref2Err", currentErr2.join(";"));
        objSecond.insert("Task4Ref3Err", currentErr3.join(";"));
        objSecond.insert("Task4Ref4Err", currentErr4.join(";"));
        objSecond.insert("Task4Ref5Err", currentErr5.join(";"));

        objSecond.insert("Task4Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else if(currentTask == 9){
        objFirst.insert("Task5Ref1Rate", lCurrentTaskRate.at(0));
        objFirst.insert("Task5Ref2Rate", lCurrentTaskRate.at(1));
        objFirst.insert("Task5Ref3Rate", lCurrentTaskRate.at(2));
        objFirst.insert("Task5Ref4Rate", lCurrentTaskRate.at(3));
        objFirst.insert("Task5Ref5Rate", lCurrentTaskRate.at(4));

        objFirst.insert("Task5Ref1Err", currentErr1.join(";"));
        objFirst.insert("Task5Ref2Err", currentErr2.join(";"));
        objFirst.insert("Task5Ref3Err", currentErr3.join(";"));
        objFirst.insert("Task5Ref4Err", currentErr4.join(";"));
        objFirst.insert("Task5Ref5Err", currentErr5.join(";"));

        objFirst.insert("Task5Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }
    else {
        objSecond.insert("Task5Ref1Rate", lCurrentTaskRate.at(0));
        objSecond.insert("Task5Ref2Rate", lCurrentTaskRate.at(1));
        objSecond.insert("Task5Ref3Rate", lCurrentTaskRate.at(2));
        objSecond.insert("Task5Ref4Rate", lCurrentTaskRate.at(3));
        objSecond.insert("Task5Ref5Rate", lCurrentTaskRate.at(4));

        objSecond.insert("Task5Ref1Err", currentErr1.join(";"));
        objSecond.insert("Task5Ref2Err", currentErr2.join(";"));
        objSecond.insert("Task5Ref3Err", currentErr3.join(";"));
        objSecond.insert("Task5Ref4Err", currentErr4.join(";"));
        objSecond.insert("Task5Ref5Err", currentErr5.join(";"));

        objSecond.insert("Task5Rate", currentTaskRate);
        //objRed.insert("TotalRate", totalRate);
    }

    QJsonObject o;
    o.insert("Red", objRed);
    o.insert("Blue", objBlue);
    emit sigFixResult(id_category, o);

}

void ControlPanel_1::slotButtonsError(bool check)
{
    int num = sender()->objectName().last(2).toInt();
    if(check) currentErr1.append(QString::number(num));
    else currentErr1.removeOne(QString::number(num));
    calculateRate1();
}

void ControlPanel_1::slotEditRate()
{
    QLineEdit* le = static_cast<QLineEdit*>(sender());
    bool ok;
    double d = le->text().toDouble(&ok);
    if(!ok || (d > 11 || d < 0)) le->setText("");
}

