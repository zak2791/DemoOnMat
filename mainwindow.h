#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "qdialog.h"
//#include "server.h"
//#include "ui_dialogConnection.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    QDialog formSettings;
    //Ui::dlgConnection uiDlg;
    QString settings;

    QListWidget* listCategories;

    Controller* controller;

    void fillMenuLastCompetitions(void);

};
#endif // MAINWINDOW_H
