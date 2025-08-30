#include "controller.h"
#include "category_0_0.h"
#include "mainwindow.h"
#include "qdebug.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    baseController = new DataBaseController(this);
    transferController = new DataTransferController(this);
    currentBaseName = "";
    lCategories = static_cast<MainWindow*>(parent)->getListCategories();
}

Controller::~Controller()
{
    delete baseController;
}

void Controller::openCompetition(QString name)
{
    QList<std::tuple<int, int, int, int, int, QString>> listData = baseController->openDataBase(name + ".db");
    if(listData.count() > 0)
        currentBaseName = name;
    else
        return;
    foreach(auto each, lCategories)
        delete each;


    foreach(auto each, listData){
        int id = std::get<0>(each);
        int id_category = std::get<1>(each);
        int id_system = std::get<2>(each);
        int mode = std::get<3>(each);
        int status = std::get<4>(each);
        QString data = std::get<5>(each);

        if(id_system == 0){
            if(mode == 0){
                Category* category = new Category_0_0(id, id_category, status, data);
                connect(category, &Category::sigSendData, transferController, &DataTransferController::sendOnMat);
                lCategory.append(category);
            }
        }



        listData.append(std::tuple(id, category, age, weight));
    }



}

void Controller::changeConnection()
{
    transferController->changeConnection();
}
