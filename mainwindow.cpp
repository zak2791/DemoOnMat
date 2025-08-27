#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QWebEngineView view;
    // view.load(QUrl("https://qt-project.org/"));
    // view.resize(1024, 750);
    // view.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
