#include "mainwindow.h"

#include "connectiondialog.h"
#include "controlpanel_0.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QActionGroup>

#include <QJsonObject>
#include <QMessageBox>

#include <QTcpServer>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    listCategories = ui->listWidget;
    controller = new Controller(listCategories, this);

    listCategories = ui->listWidget;

    connect(ui->actConnection, &QAction::triggered, this, [this](){
        ConnectionDialog dlg;
        int ret = dlg.exec();
        if(ret == QDialog::Accepted)
            controller->changeConnection();
    });

    fillMenuLastCompetitions();

    connectionStatus = new ConnectionStatus;
    lblStatus = new QLabel(this);
    status = new QStatusBar(this);
    status->addWidget(lblStatus);
    status->addPermanentWidget(connectionStatus);
    setStatusBar(status);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCategoryScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

void MainWindow::setControlPanel(QWidget * wgt)
{
    ui->verticalLayout->addWidget(wgt);
}

void MainWindow::removeControlPanel(QWidget * wgt)
{
    ui->verticalLayout->removeWidget(wgt);
}

void MainWindow::turnOnStatus()
{
    connectionStatus->setStatusOn();
}

void MainWindow::openCompetition(QString text)
{
    lblStatus->setText(text);
}


QJsonDocument MainWindow::getCurrentData()
{

    QJsonObject Obj;

    return QJsonDocument(Obj);
}

void MainWindow::fillMenuLastCompetitions()
{
    QDir dir = QDir::current();
    QFileInfoList lFiles = dir.entryInfoList({"*.db"}, QDir::Files, QDir::Time);
    if(lFiles.count() > 0){
        QActionGroup* gr = new QActionGroup(this);
        foreach(QFileInfo inf, lFiles){
            QAction* act = gr->addAction(inf.completeBaseName());
            act->setCheckable(true);
            connect(act, &QAction::triggered, this, [act, this]{
                controller->openCompetition(act->text());
            });
        }
        ui->mOpenLast->addActions(gr->actions());
    }

}
