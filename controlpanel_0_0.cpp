#include "controlpanel_0_0.h"
#include "ui_controlpanel_0_0.h"

ControlPanel_0_0::ControlPanel_0_0(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlPanel_0_0)
{
    ui->setupUi(this);
}

ControlPanel_0_0::~ControlPanel_0_0()
{
    delete ui;
}
