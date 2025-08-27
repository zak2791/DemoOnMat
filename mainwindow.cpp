#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"agt";
    // QWebEngineView view;
    // view.load(QUrl("https://qt-project.org/"));
    // view.resize(1024, 750);
    // view.show();

    server = new Server(this);

    uiDlg.setupUi(&formSettings);

    connect(uiDlg.sbPortTCP, &QSpinBox::valueChanged, this, [this](int value){
        QSettings settings("settings.ini", QSettings::IniFormat);
        settings.beginGroup("connections");
        settings.setValue("tcpPort", value);
        settings.endGroup();
        server->setPort(value);
    });

    connect(ui->actConnection, &QAction::triggered, this, [this](){
        qDebug()<<"agt";
        int ret = formSettings.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
