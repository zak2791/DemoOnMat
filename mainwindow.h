#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectionstatus.h"
#include "controller.h"
#include "qdialog.h"


#include <QMainWindow>

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
    void setCategoryScene(QGraphicsScene*);
    void setControlPanel(QWidget*);
    void removeControlPanel(QWidget*);
    void turnOnStatus(void);
    void openCompetition(QString);


private:
    Ui::MainWindow *ui;
    QDialog formSettings;

    QString settings;

    QListWidget* listCategories;

    Controller* controller;


    QJsonDocument getCurrentData();

    void fillMenuLastCompetitions(void);
    ConnectionStatus* connectionStatus;
    QStatusBar* status;
    QLabel* lblStatus;


};
#endif // MAINWINDOW_H
