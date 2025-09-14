#include "controller.h"
#include "category_0_0.h"
#include "controlpanel_0_0.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "qjsonobject.h"

Controller::Controller(QListWidget* list, QObject *parent)
    : QObject{parent}
{
    baseController = new DataBaseController(this);
    currentBaseName = "";
    transferController = new DataTransferController(&currentBaseName, this);
    listWidget = list;
    p = parent;
}

Controller::~Controller()
{
    delete baseController;
    foreach (auto each, listCategories)
        delete each;
}

void Controller::openCompetition(QString name)
{
    QList<std::tuple<int, int, int, int, int, QString, QString, QString, QString>> listData = baseController->readCategories(name + ".db");
    currentBaseName = name;
    if(listData.count() == 0)
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
        QString category = std::get<5>(each);
        QString age = std::get<6>(each);
        QString weight = std::get<7>(each);
        QString data = std::get<8>(each);

        if(id_system == 0){
            if(mode == 0){
                Category* cat = new Category_0_0(id, id_category, status, category, age, weight, data);
                connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
                connect(cat, &Category::sigDataControlPanel, this, &Controller::slotDataControlPanel);
                connect(cat, &Category::sigSaveData, this, &Controller::slotSaveData);
                //connect(cat, &Category::sigSendData, transferController, &DataTransferController::sendOnMat);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                item->setData(Qt::UserRole, id);
                listWidget->addItem(item);
                listWidget->setItemWidget(item, cat);
            }
        }
    }
}

void Controller::changeConnection()
{
    transferController->changeConnection();
}

bool Controller::addCategory(QString _data)
{
    QJsonDocument doc = QJsonDocument::fromJson(_data.toUtf8());
    QJsonObject obj = doc.object();
    int id_base = obj.value("Id_category").toInt();
    foreach(auto each, listCategories)
        if(each->getBaseCategory() == id_base)
            return true;                        //категория уже существует
    int id_system = obj.value("Id_system").toInt();
    int mode = obj.value("Mode").toInt();
    QString category =  obj.value("Category").toString();
    QString age =  obj.value("Age").toString();
    QString weight =  obj.value("Weight").toString();
    QJsonArray data = obj.value("Data").toArray();

    QJsonArray mainArray;
    for(int i = 0; i < data.size(); i++){
        QJsonObject o = data.at(i).toObject();
        o.insert("CurrentTask", 0);
        o.insert("TotalRate", 0.0);
        o.insert("Task1Rate", 0.0);
        o.insert("Task2Rate", 0.0);
        o.insert("Task3Rate", 0.0);
        o.insert("Task4Rate", 0.0);
        o.insert("Task5Rate", 0.0);
        o.insert("Task1Ref1Rate", 0.0);
        o.insert("Task1Ref2Rate", 0.0);
        o.insert("Task1Ref3Rate", 0.0);
        o.insert("Task1Ref4Rate", 0.0);
        o.insert("Task1Ref5Rate", 0.0);
        o.insert("Task2Ref1Rate", 0.0);
        o.insert("Task2Ref2Rate", 0.0);
        o.insert("Task2Ref3Rate", 0.0);
        o.insert("Task2Ref4Rate", 0.0);
        o.insert("Task2Ref5Rate", 0.0);
        o.insert("Task3Ref1Rate", 0.0);
        o.insert("Task3Ref2Rate", 0.0);
        o.insert("Task3Ref3Rate", 0.0);
        o.insert("Task3Ref4Rate", 0.0);
        o.insert("Task3Ref5Rate", 0.0);
        o.insert("Task4Ref1Rate", 0.0);
        o.insert("Task4Ref2Rate", 0.0);
        o.insert("Task4Ref3Rate", 0.0);
        o.insert("Task4Ref4Rate", 0.0);
        o.insert("Task4Ref5Rate", 0.0);
        o.insert("Task5Ref1Rate", 0.0);
        o.insert("Task5Ref2Rate", 0.0);
        o.insert("Task5Ref3Rate", 0.0);
        o.insert("Task5Ref4Rate", 0.0);
        o.insert("Task5Ref5Rate", 0.0);
        o.insert("Task1Ref1Err", "");
        o.insert("Task1Ref2Err", "");
        o.insert("Task1Ref3Err", "");
        o.insert("Task1Ref4Err", "");
        o.insert("Task1Ref5Err", "");
        o.insert("Task2Ref1Err", "");
        o.insert("Task2Ref2Err", "");
        o.insert("Task2Ref3Err", "");
        o.insert("Task2Ref4Err", "");
        o.insert("Task2Ref5Err", "");
        o.insert("Task3Ref1Err", "");
        o.insert("Task3Ref2Err", "");
        o.insert("Task3Ref3Err", "");
        o.insert("Task3Ref4Err", "");
        o.insert("Task3Ref5Err", "");
        o.insert("Task4Ref1Err", "");
        o.insert("Task4Ref2Err", "");
        o.insert("Task4Ref3Err", "");
        o.insert("Task4Ref4Err", "");
        o.insert("Task4Ref5Err", "");
        o.insert("Task5Ref1Err", "");
        o.insert("Task5Ref2Err", "");
        o.insert("Task5Ref3Err", "");
        o.insert("Task5Ref4Err", "");
        o.insert("Task5Ref5Err", "");

        mainArray.append(o);
    }
    QJsonDocument _doc(mainArray);
    QString strJson(_doc.toJson(QJsonDocument::Compact));

    int id = baseController->addCategory(id_base, id_system, mode, category, age, weight, strJson);
    if(id == -1)
        return false;

    if(id_system == 0){
        if(mode == 0){
            Category* cat = new Category_0_0(id, id_base, 0, category, age, weight, strJson);
            listCategories.append(cat);
        }
    }
    return true;
}

void Controller::setCategoryScene(QGraphicsScene * scene)
{
    static_cast<MainWindow*>(p)->setCategoryScene(scene);
}

void Controller::slotDataControlPanel(int _id, int _id_system, QJsonObject obj)
{
    if(panel != nullptr){
        if(panel->getIdSystem() != _id_system){
            static_cast<MainWindow*>(p)->removeControlPanel(panel);
            delete panel;
            if(_id_system == 0)
                panel = new ControlPanel_0_0;
            else
                panel = new ControlPanel_0_0;
            static_cast<MainWindow*>(p)->setControlPanel(panel);
            connect(panel, &ControlPanel::sigFixResult, this, &Controller::slotFixResult);
        }
    }
    else{
        if(_id_system == 0)
            panel = new ControlPanel_0_0;
        else
            panel = new ControlPanel_0_0;
        static_cast<MainWindow*>(p)->setControlPanel(panel);
    }
    panel->setData(_id, obj);
    connect(panel, &ControlPanel::sigFixResult, this, &Controller::slotFixResult);
}

void Controller::slotFixResult(int id, QJsonObject obj)
{
    foreach(auto each, listCategories){
        if(id == each->getId()){
            each->setDataFromControlPanel(obj);
            return;
        }
    }
}

void Controller::slotSaveData(int id, QString strJson)
{
    baseController->writeData(id, strJson);
}
