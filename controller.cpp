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
    listWidget = static_cast<MainWindow*>(parent)->getListCategories();
}

Controller::~Controller()
{
    delete baseController;
    foreach (auto each, listCategories)
        delete each;
}

void Controller::openCompetition(QString name)
{
    QList<std::tuple<int, int, int, int, int, QString>> listData = baseController->openDataBase(name + ".db");
    if(listData.count() > 0)
        currentBaseName = name;
    else
        return;
    foreach (auto each, listCategories)
        delete each;
    listCategories.clear();

    foreach(auto each, listData){
        int id = std::get<0>(each);
        int id_category = std::get<1>(each);
        int id_system = std::get<2>(each);
        int mode = std::get<3>(each);
        int status = std::get<4>(each);
        QString data = std::get<5>(each);

        if(id_system == 0){
            if(mode == 0){
                Category* cat = new Category_0_0(id, id_category, status, data);
                //connect(cat, &Category::sigSendData, transferController, &DataTransferController::sendOnMat);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                item->setData(Qt::UserRole, id);
                (*listWidget).addItem(item);
                (*listWidget).setItemWidget(item, cat);
            }
        }
        //listData.append(std::tuple(id, category, age, weight));
    }
}

void Controller::changeConnection()
{
    transferController->changeConnection();
}

void Controller::addCategory(QString _data)
{
    int id_base;
    int id_system;
    int mode;
    QString data;
    int id = baseController->addCategory(id_base, id_system, mode, data);
    if(id == -1){
        qDebug()<<"Ошибка добавления категории";
        return;
    }
}
