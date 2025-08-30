#include "mainwindow.h"

#include "connectiondialog.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controller = new Controller(this);
    //server = new Server(this);
    listCategories = ui->listWidget;

    connect(ui->actConnection, &QAction::triggered, this, [this](){
        ConnectionDialog dlg;
        int ret = dlg.exec();
        if(ret == QDialog::Accepted)
            controller->changeConnection();
    });

    fillMenuLastCompetitions();
}

MainWindow::~MainWindow()
{
    delete ui;
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
