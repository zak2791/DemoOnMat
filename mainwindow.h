#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "qdialog.h"
//#include "qwebengineview.h"
//#include "server.h"
//#include "ui_dialogConnection.h"
#include <QMainWindow>
#include <QHttpServer>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QListWidget* getListCategories(void){return listCategories;}

public slots:
    void httpServerSetup();

private:
    Ui::MainWindow *ui;
    QDialog formSettings;
    //Ui::dlgConnection uiDlg;
    QString settings;

    QListWidget* listCategories;

    Controller* controller;
    QHttpServer *httpServer;
    void httpServerCreate();
    QJsonDocument getCurrentData();

    void fillMenuLastCompetitions(void);

    //QWebEngineView* view;

};
#endif // MAINWINDOW_H
