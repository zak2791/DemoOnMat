#include "mainwindow.h"

#include "connectiondialog.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QActionGroup>
#include <QHttpServer>
#include <QTcpServer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView* view = ui->widget;
    view->load(QUrl("127.0.0.1:7000"));
    // view->resize(1024, 750);
    // view->show();

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

    QHttpServer* server = new QHttpServer(this);

    QString http = "<html>"
                   "<head>"
                   "<meta charset='utf-8'>"
                   "</head>"
                   "<body>"
                   "<h1>Hello!</h1>"
                   "</body>"
                   "</html>";
    server->route("/", [&http] () {
        return "hello";
    });

    auto tcpserver = new QTcpServer(this);

    if (!tcpserver->listen(QHostAddress::Any, 7000) || !server->bind(tcpserver)) {
        delete tcpserver;
        //return -1;
    }
    qDebug() << "Listening on port" << tcpserver->serverPort();
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
